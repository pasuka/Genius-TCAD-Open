/********************************************************************************/
/*     888888    888888888   88     888  88888   888      888    88888888       */
/*   8       8   8           8 8     8     8      8        8    8               */
/*  8            8           8  8    8     8      8        8    8               */
/*  8            888888888   8   8   8     8      8        8     8888888        */
/*  8      8888  8           8    8  8     8      8        8            8       */
/*   8       8   8           8     8 8     8      8        8            8       */
/*     888888    888888888  888     88   88888     88888888     88888888        */
/*                                                                              */
/*       A Three-Dimensional General Purpose Semiconductor Simulator.           */
/*                                                                              */
/*                                                                              */
/*  Copyright (C) 2007-2008                                                     */
/*  Cogenda Pte Ltd                                                             */
/*                                                                              */
/*  Please contact Cogenda Pte Ltd for license information                      */
/*                                                                              */
/*  Author: Gong Ding   gdiso@ustc.edu                                          */
/*                                                                              */
/********************************************************************************/


#include "genius_common.h"
#include "genius_env.h"

#include <cctype>
#include <ios>
#include <fstream>
#include <string>

#ifdef HAVE_SLEPC
  #include "slepcsys.h"
#endif

// ------------------------------------------------------------
// Genius::GeniusPrivateData data initialization
int  Genius::GeniusPrivateData::_n_processors = 1;
int  Genius::GeniusPrivateData::_processor_id = 0;

#ifdef HAVE_MPI
MPI_Comm Genius::GeniusPrivateData::_comm_world;
MPI_Comm Genius::GeniusPrivateData::_comm_self;
#endif

std::string Genius::GeniusPrivateData::_input_file;
std::string Genius::GeniusPrivateData::_genius_dir;

bool Genius::GeniusPrivateData::_experiment_code=true;

bool Genius::init_processors(int *argc, char *** args)
{
  // GENIUS is built on top of PETSC, we should init PETSC first
#ifdef HAVE_SLEPC
  // if we have slepc, call  SlepcInitialize instead of PetscInitialize
  SlepcInitialize(argc,args,PETSC_NULL,PETSC_NULL);
#else
  PetscInitialize(argc, args, PETSC_NULL, PETSC_NULL);
#endif

#ifdef HAVE_MPI
  // the actual process number
  MPI_Comm_size (PETSC_COMM_WORLD, &Genius::GeniusPrivateData::_n_processors);
  MPI_Comm_rank (PETSC_COMM_WORLD, &Genius::GeniusPrivateData::_processor_id);

  // duplicate an other MPI_Comm for Genius parallel communication
  MPI_Comm_dup( PETSC_COMM_WORLD, &Genius::GeniusPrivateData::_comm_world );
  MPI_Comm_dup( PETSC_COMM_SELF, &Genius::GeniusPrivateData::_comm_self );
#endif

  return true;
}

bool Genius::clean_processors()
{

#ifdef HAVE_MPI
  MPI_Comm_free(&Genius::GeniusPrivateData::_comm_world);
  MPI_Comm_free(&Genius::GeniusPrivateData::_comm_self);
#endif

  // end PETSC
#ifdef  HAVE_SLEPC
  SlepcFinalize();
#else
  PetscFinalize();
#endif


  return true;
}


#ifdef WINDOWS
  #include <windows.h>
#else
  #include <unistd.h>
  #include <climits>
  #include <sys/time.h>
  #include <sys/resource.h>
#endif



std::pair<size_t, size_t> Genius::memory_size()
{
#ifdef WINDOWS
#else

   // 'file' stat seems to give the most reliable results
   //
   std::ifstream stat_stream("/proc/self/statm", std::ios_base::in);

   size_t vsize; // Virtual memory size in pages.
   size_t rss;   // Resident Set Size in pages

   stat_stream >> vsize >> rss; // don't care about the rest

   stat_stream.close();

   size_t page_size = sysconf(_SC_PAGE_SIZE);

   return std::make_pair(vsize*page_size, rss*page_size);

#endif
  //return 0;

}


#ifdef WINDOWS
// Convert a MSYS2/Cygwin POSIX-style path to a native Windows path so that
// Win32 APIs such as LoadLibraryEx() can resolve it correctly.
//
// Examples:
//   /d/code-repo/Genius-TCAD-Open  →  D:\code-repo\Genius-TCAD-Open
//   /c/Program Files/genius        →  C:\Program Files\genius
//
// Paths that do not match the /<letter>/<rest> pattern are returned unchanged,
// so a caller that already has a proper Windows path is unaffected.
static std::string normalize_windows_path(const std::string &path)
{
  // MSYS2/Cygwin encodes the Windows drive D: as /d/ at the start of the path.
  if (path.size() >= 3 &&
      path[0] == '/' &&
      std::isalpha(static_cast<unsigned char>(path[1])) &&
      path[2] == '/')
  {
    std::string win_path;
    win_path.reserve(path.size());
    win_path += static_cast<char>(std::toupper(static_cast<unsigned char>(path[1])));
    win_path += ':';
    win_path += '\\';
    for (std::size_t i = 3; i < path.size(); ++i)
      win_path += (path[i] == '/') ? '\\' : path[i];
    return win_path;
  }
  return path;
}
#endif // WINDOWS


void Genius::set_genius_dir(const std::string &genius_dir)
{
#ifdef WINDOWS
  GeniusPrivateData::_genius_dir = normalize_windows_path(genius_dir);
#else
  GeniusPrivateData::_genius_dir = genius_dir;
#endif
}


std::string Genius::auto_detect_genius_dir()
{
  // The expected layout is $GENIUS_DIR/bin/genius (or genius.exe on Windows).
  // We resolve the path of the running executable, strip the binary name to
  // get its containing directory, and then strip one more level to obtain the
  // installation prefix that should serve as GENIUS_DIR.

#ifdef WINDOWS
  char buf[MAX_PATH];
  DWORD len = GetModuleFileNameA(NULL, buf, MAX_PATH);
  if (len == 0 || len >= MAX_PATH) return std::string();
  std::string exe_path(buf, len);
  // Strip executable name → bin directory
  std::string::size_type pos = exe_path.rfind('\\');
  if (pos == std::string::npos) return std::string();
  std::string bin_dir = exe_path.substr(0, pos);
  // Strip bin directory → installation prefix
  pos = bin_dir.rfind('\\');
  if (pos == std::string::npos) return std::string();
  return bin_dir.substr(0, pos);
#else
  char buf[PATH_MAX];
  ssize_t len = readlink("/proc/self/exe", buf, sizeof(buf) - 1);
  if (len <= 0) return std::string();
  buf[len] = '\0';
  std::string exe_path(buf);
  // Strip executable name → bin directory
  std::string::size_type pos = exe_path.rfind('/');
  if (pos == std::string::npos) return std::string();
  std::string bin_dir = exe_path.substr(0, pos);
  // Strip bin directory → installation prefix
  pos = bin_dir.rfind('/');
  if (pos == std::string::npos) return std::string();
  return bin_dir.substr(0, pos);
#endif
}



