#include "FFGL.hpp"
#include "ParameterTemplate.hpp"
#include "PluginManager.hpp"

PluginManager manager;

#ifdef WIN32
plugMainUnion __stdcall plugMain(DWORD functionCode, DWORD inputValue, DWORD instanceID) 
#elif defined(__linux__) || defined(TARGET_OS_MAC)
plugMainUnion plugMain(DWORD functionCode, DWORD inputValue, DWORD instanceID)
#else
#error add plugMain signature for your OS
#endif
{
    Plugin* instance = reinterpret_cast<Plugin*>(instanceID);
    plugMainUnion ret;

    try {
        switch(functionCode)
        {
            case FF_GETINFO: {
                ret.PISvalue = manager.getInfo();
                break;
            }
            case FF_INITIALISE: {
                ret.ivalue = manager.initialise();
                break;
            }
            case FF_DEINITIALISE: {
                ret.ivalue = manager.deinitialise();
                break;
            }
            case FF_GETNUMPARAMETERS: {
                ret.ivalue = manager.getNumParameters();
                break;
            }
            case FF_GETPARAMETERNAME: {
                char* output = manager.getParameterName(inputValue);
                if (output == nullptr)
                    ret.ivalue = FF_FAIL;
                else
                    ret.svalue = output;
                break;
            }
            case FF_GETPARAMETERDEFAULT: {
                ret.ivalue = manager.getParameterDefault(inputValue).Data;
                break;
            }
            case FF_GETPARAMETERDISPLAY: {
                if (!manager.isPlugin(instance)) {
                    ret.ivalue = FF_FAIL;
                    break;
                }

                char* output = instance->getParameterDisplay(inputValue);
                if (output == nullptr)
                    ret.ivalue = FF_FAIL;
                else
                    ret.svalue = output;
                break;
            }
            case FF_SETPARAMETER: {
                if (!manager.isPlugin(instance)) {
                    ret.ivalue = FF_FAIL;
                    break;
                }

                SetParameterStruct* input = reinterpret_cast<SetParameterStruct*>(inputValue);
                ParameterValue value;
                value.Data = input->NewParameterValue;
                ret.ivalue = instance->setParameterValue(input->ParameterNumber, value);
                break;
            }
            case FF_GETPARAMETER: {
                if (!manager.isPlugin(instance)) {
                    ret.ivalue = FF_FAIL;
                    break;
                }

                ret.ivalue = instance->getParameterValue(inputValue).Data;
                break;
            }
            case FF_GETPLUGINCAPS: {
                ret.ivalue = manager.getPluginCapability(inputValue);
                break;
            }
            case FF_GETEXTENDEDINFO: {
                ret.ivalue = reinterpret_cast<DWORD>(manager.getExtendedInfo());
                break;
            }
            case FF_GETPARAMETERTYPE: {
                ret.ivalue = manager.getParameterType(inputValue);
                break;
            }
            case FF_GETINPUTSTATUS: {
                ret.ivalue = FF_FAIL;
                break;
            }
            case FF_PROCESSOPENGL: {
                if (!manager.isPlugin(instance)) {
                    ret.ivalue = FF_FAIL;
                    break;
                }

                ProcessOpenGLStruct* ogl_data = reinterpret_cast<ProcessOpenGLStruct*>(inputValue);
                ret.ivalue = instance->processOpenGL(ogl_data);
                break;
            }
            case FF_INSTANTIATEGL: {
                FFGLViewportStruct* viewport = reinterpret_cast<FFGLViewportStruct*>(inputValue);
                ret.ivalue = reinterpret_cast<DWORD>(manager.instantiateGL(viewport));
                break;
            }
            case FF_DEINSTANTIATEGL: {
                if (!manager.isPlugin(instance)) {
                    ret.ivalue = FF_FAIL;
                    break;
                }

                ret.ivalue = manager.deInstantiateGL(instance);
                break;
            }
            case FF_SETTIME: {
                if (!manager.isPlugin(instance)) {
                    ret.ivalue = FF_FAIL;
                    break;
                }

                double time = *reinterpret_cast<double*>(inputValue);
                ret.ivalue = instance->setTime(time);
                break;
            }
            case FF_INSTANTIATE:       // These always fail for GL
            case FF_DEINSTANTIATE:
            case FF_PROCESSFRAME:
            case FF_PROCESSFRAMECOPY:
            default: {                 // Don't know what to do - assume fail
                ret.ivalue = FF_FAIL;
                break;
            }
        }
    } 
    catch(...) {
        ret.ivalue = FF_FAIL;
    }
    return ret;
}
