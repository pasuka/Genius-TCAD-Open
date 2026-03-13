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

//  $Id: dlhook.cc,v 1.5 2008/07/09 05:58:16 gdiso Exp $

#include "dlhook.h"
#include "solver_base.h"

#ifdef DLLHOOK

#ifdef WINDOWS
#include <windows.h>
#else
#include <dlfcn.h>
#endif

DllHook::DllHook(SolverBase & solver, const std::string & name, void * fun_data)
:Hook(solver, name), dll_handle(0), hook(0)
{
  std::string genius_dir(Genius::genius_dir());
  std::string filename =  genius_dir + "/lib/" + name + ".so";

#ifdef WINDOWS
  // Use Windows LoadLibrary to load the hook DLL
  dll_handle = (void *) LoadLibraryA(filename.c_str());
  if(!dll_handle)
  {
    DWORD err = GetLastError();
    std::cerr << "Load hook failed: Windows error code " << err << std::endl;
    return;
  }

  // get the address of function get_hook in the dll file
  get_hook = (GET_HOOK *) GetProcAddress((HMODULE)dll_handle, "get_hook");
  if(!get_hook)
  {
    DWORD err = GetLastError();
    std::cerr << "Load hook failed: Windows error code " << err << std::endl;
    FreeLibrary((HMODULE)dll_handle);
    dll_handle = NULL;
    return;
  }
#else
  char * error;

  // Get 'dlopen()' handle to the extension function
#ifdef RTLD_DEEPBIND
  dll_handle = dlopen(filename.c_str(),RTLD_LAZY|RTLD_DEEPBIND);
#else
  dll_handle = dlopen(filename.c_str(),RTLD_LAZY);
#endif
  error = dlerror();
  if(error)
  {
    std::cerr<< "Load hook faild: "<< error << std::endl;
    dll_handle = NULL;
    return;
  }

  // get the address of function get_hook in the dll file
  get_hook = (GET_HOOK *) dlsym(dll_handle, "get_hook");
  error = dlerror();
  if(error)
  {
    std::cerr<< "Load hook faild: "<< error << std::endl;
    dll_handle = NULL;
    return;
  }
#endif

  // call it to get the real hook pointer
  hook = (*get_hook)(_solver, _name, fun_data);
  genius_assert(hook);

}



DllHook::~DllHook()
{
  if(hook) delete hook;
#ifdef WINDOWS
  if(dll_handle) FreeLibrary((HMODULE)dll_handle);
#else
  if(dll_handle) dlclose(dll_handle);
#endif
}

#endif
