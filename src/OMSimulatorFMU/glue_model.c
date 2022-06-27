#include <stdio.h>
#include <string.h>

#include "glue_model.h"
#define OMS_STATIC 1
#include "OMSimulator.h"
#include <fmilib.h>


typedef struct {
  jm_callbacks callbacks;
  fmi2_callback_functions_t callbackFunctions;
  fmi_import_context_t* context;
  fmi2_import_t* fmu;

} fmilibcomp_t;

typedef fmilibcomp_t* fmilibcomp_ptr_t;

void oms_fmiLogger(jm_callbacks* c, jm_string module, jm_log_level_enu_t log_level, jm_string message)
{
  switch (log_level)
  {
  case jm_log_level_info:    // Informative messages
    //logDebug("module " + std::string(module) + ": " + std::string(message));
    break;
  case jm_log_level_warning: // Non-critical issues
    //logWarning("module " + std::string(module) + ": " + std::string(message));
    break;
  case jm_log_level_error:   // Errors that may be not critical for some FMUs
  case jm_log_level_fatal:   // Unrecoverable errors
    //logError("module " + std::string(module) + ": " + std::string(message));
    break;
  case jm_log_level_verbose: // Verbose messages
  case jm_log_level_debug:   // Debug messages. Only enabled if library is configured with FMILIB_ENABLE_LOG_LEVEL_DEBUG
    //logDebug("[log level " + std::string(jm_log_level_to_string(log_level)) + "] module " + std::string(module) + ": " + std::string(message));
  }
}

void oms_fmi2logger(fmi2_component_environment_t env, fmi2_string_t instanceName, fmi2_status_t status, fmi2_string_t category, fmi2_string_t message, ...)
{
  if ((status == fmi2_status_ok || status == fmi2_status_pending))
  {
    // When frequently called for debug logging during simulation, avoid costly formatting.
    return;
  }

  int len;
  char msg[1000];
  va_list argp;
  va_start(argp, message);
  len = vsnprintf(msg, 1000, message, argp);

  switch (status)
  {
  case fmi2_status_ok:
  case fmi2_status_pending:
    //logDebug(std::string(instanceName) + " (" + category + "): " + msg);
    break;
  case fmi2_status_warning:
    //logWarning(std::string(instanceName) + " (" + category + "): " + msg);
    break;
  case fmi2_status_discard:
  case fmi2_status_error:
  case fmi2_status_fatal:
    //logError(std::string(instanceName) + " (" + category + "): " + msg);
    break;
  default:
    //logWarning("fmiStatus = " + std::string(fmi2_status_to_string(status)) + "; " + instanceName + " (" + category + "): " + msg);
  }
}

void parseXML(fmilibcomp_ptr_t fc, fmi2String fmuLocation) {
	fc->callbacks.malloc = malloc;
	fc->callbacks.calloc = calloc;
	fc->callbacks.realloc = realloc;
	fc->callbacks.free = free;
	fc->callbacks.logger = oms_fmiLogger;
	fc->callbacks.log_level = jm_log_level_all;
	fc->callbacks.context = 0;
}


/* Model calculation functions */
static int calc_initialize(component_ptr_t comp)
{

//	if(comp->loggingOn) 
//  {
//		comp->functions->logger(comp->functions->componentEnvironment, comp->instanceName, fmi2OK, "INFO", "###### Initializing component ######");
//	}
	return 0;
}

static int calc_get_derivatives(component_ptr_t comp)
{
	return 0;
}

static int calc_get_event_indicators(component_ptr_t comp)
{	
	return 0;
}

static int calc_event_update(component_ptr_t comp)
{	
    return 0;
}


/* FMI 2.0 Common Functions */
const char* fmi_get_version()
{
	return FMI_VERSION;
}

fmi2Status fmi_set_debug_logging(fmi2Component c, fmi2Boolean loggingOn)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) {
		return fmi2Fatal;
	} else {
		comp->loggingOn = loggingOn;
		return fmi2OK;
	}
}

fmi2Status fmi_get_real(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Real value[])
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
        size_t i;
        for(i=0; i<nvr; ++i)
        {
            value[i] = getReal(vr[i]);
        }
		return fmi2OK;
	}
}

fmi2Status fmi_get_integer(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Integer value[])
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
//        size_t i;
//        for(i=0; i<nvr; ++i)
//        {
//            value[i] = hopsan_get_integer(vr[i]);
//        }
		return fmi2OK;
	}
}

fmi2Status fmi_get_boolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2Boolean value[])
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
//       size_t i;
//        for(i=0; i<nvr; ++i)
//        {
//            value[i] = hopsan_get_boolean(vr[i]);
//        }
        return fmi2OK;
	}
}

fmi2Status fmi_get_string(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, fmi2String  value[])
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
//        size_t i;
//        for(i=0; i<nvr; ++i)
//        {
//            value[i] = hopsan_get_string(vr[i]);
//        }
		return fmi2OK;
	}
}

fmi2Status fmi_set_real(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Real value[])
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
        size_t i;
        for(i=0; i<nvr; ++i)
        {
            setReal(vr[i],value[i]);
        }
		return fmi2OK;
	}
}

fmi2Status fmi_set_integer(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer value[])
{
    component_ptr_t comp = (component_ptr_t)c;
    if (comp == NULL)
    {
        return fmi2Fatal;
    }
    else
    {
        return fmi2OK;
    }
}

fmi2Status fmi_set_boolean(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Boolean value[])
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
//        size_t i;
//        for(i=0; i<nvr; ++i)
//        {
//            hopsan_set_boolean(vr[i], value[i]);
//        }
		return fmi2OK;
	}
}

fmi2Status fmi_set_string(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2String  value[])
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
//        size_t i;
//        for(i=0; i<nvr; ++i)
//        {
//            hopsan_set_string(vr[i], value[i]);
//        }
        return fmi2OK;
	}
}

/* FMI 2.0 ME Functions */
const char* fmi_get_model_types_platform()
{
    return fmi2TypesPlatform;
}

/* static FILE* find_string(FILE* fp, char* str, int len) {

} */

fmi2Component fmi_instantiate(fmi2String instanceName, fmi2Type fmuType,
  fmi2String fmuGUID, fmi2String fmuLocation,
  const fmi2CallbackFunctions *functions, fmi2Boolean visible,
  fmi2Boolean loggingOn)
{
	component_ptr_t comp;
	int k, p;
	char sspFile[1024];
	char* cref;
	fmilibcomp_ptr_t fmilibcomp;

  fmilibcomp = (fmilibcomp_ptr_t)functions->allocateMemory(1, sizeof(fmilibcomp_t));
	if (fmilibcomp == NULL) {
		return NULL;
	} 

	comp = (component_ptr_t)functions->allocateMemory(1, sizeof(component_t));
	if (comp == NULL) {
		return NULL;
	} 

	if (strcmp(fmuGUID, FMI_GUID) != 0) {
		fprintf(stderr, "FMU XML GUID[%s] != FMU C GUID [%s]\n", fmuGUID, FMI_GUID);
	} 
	sprintf(comp->instanceName, "%s", instanceName);
	sprintf(comp->GUID, "%s", fmuGUID);
	fprintf(stderr, "%s/%s\n", fmuLocation, instanceName); fflush(NULL);
	comp->functions		= functions;
	/*comp->functions->allocateMemory = functions->allocateMemory;*/
	comp->loggingOn		= loggingOn;

	for(int i=8; i < strlen(fmuLocation); i++)
			sspFile[i-8] = fmuLocation[i];
	sspFile[strlen(fmuLocation)-8] = '\0';
	sprintf(sspFile, "%s/%s.%s", strdup(sspFile), instanceName, ".ssp");
	oms_importFile(sspFile, &cref);
	sprintf(comp->cref, "%s", cref);

	sprintf(comp->fmuLocation, "%s", fmuLocation);
	comp->visible		= visible;

	// parse the XML file
	parseXML(fmilibcomp, fmuLocation);

	return comp;
}

void fmi_free_instance(fmi2Component c)
{
	int i;
	component_ptr_t comp = (component_ptr_t)c;
	for(i = 0; i < N_STRING; i++) {
		comp->functions->freeMemory((void*)(comp->strings[i]));
		comp->strings[i] = 0;
	}
	comp->functions->freeMemory(c);
}

fmi2Status fmi_setup_experiment(fmi2Component c, fmi2Boolean toleranceDefined,
                               fmi2Real tolerance, fmi2Real startTime,
                               fmi2Boolean stopTimeDefined,
                               fmi2Real stopTime)
{
    component_ptr_t comp = (component_ptr_t)c;

    if (comp == NULL) 
    {
        return fmi2Fatal;
    } 
    else 
    {
        comp->toleranceControlled = toleranceDefined;
        comp->relativeTolerance = tolerance;

        comp->tStart = startTime;
        comp->StopTimeDefined = stopTimeDefined;
        comp->tStop = stopTime;

        return fmi2OK;
    }
}

fmi2Status fmi_enter_initialization_mode(fmi2Component c)
{
    if (c == NULL) 
    {
        return fmi2Fatal;
    } 
    else 
    {
        calc_initialize((component_ptr_t)c);
        return fmi2OK;
    }
}

fmi2Status fmi_exit_initialization_mode(fmi2Component c)
{
    return fmi2OK;
}

fmi2Status fmi_enter_event_mode(fmi2Component c)
{
    return fmi2OK;
}

fmi2Status fmi_new_discrete_states(fmi2Component c, fmi2EventInfo* eventInfo)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		calc_event_update(comp);

		*eventInfo = comp->eventInfo;
		return fmi2OK;
	}
}

fmi2Status fmi_enter_continuous_time_mode(fmi2Component c)
{
    return fmi2OK;
}

fmi2Status fmi_set_time(fmi2Component c, fmi2Real fmitime)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		comp->fmitime = fmitime;
		return fmi2OK;
	}
}

fmi2Status fmi_set_continuous_states(fmi2Component c, const fmi2Real x[], size_t nx)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		size_t k;
		for (k = 0; k < nx; k++) 
        {
			comp->states[k] = x[k];
		}
		return fmi2OK;
	}
}

fmi2Status fmi_completed_integrator_step(fmi2Component c,
  fmi2Boolean noSetFMUStatePriorToCurrentPoint,
  fmi2Boolean* enterEventMode, fmi2Boolean* terminateSimulation)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		*enterEventMode = fmi2False;
		return fmi2OK;
	}
}

fmi2Status fmi_get_derivatives(fmi2Component c, fmi2Real derivatives[] , size_t nx)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		size_t k;

		calc_get_derivatives(comp);

		for (k = 0; k < nx; k++) {
			derivatives[k] = comp->states_der[k];
		}
		return fmi2OK;
	}
}

fmi2Status fmi_get_event_indicators(fmi2Component c, fmi2Real eventIndicators[], size_t ni)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		size_t k;

		calc_get_event_indicators(comp);

		for (k = 0; k < ni; k++) 
        {
			eventIndicators[k] = comp->event_indicators[k];
		}
		return fmi2OK;
	}
}

fmi2Status fmi_get_continuous_states(fmi2Component c, fmi2Real states[], size_t nx)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		size_t k;

		for (k = 0; k < nx; k++) 
        {
			states[k] = comp->states[k];
		}
		return fmi2OK;
	}
}

fmi2Status fmi_get_nominals_of_continuousstates(fmi2Component c, fmi2Real x_nominal[], size_t nx)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		size_t k;
		for (k = 0; k < nx; k++) 
        {
			x_nominal[k] = comp->states_nom[k];
		}
		return fmi2OK;
	}
}

fmi2Status fmi_terminate(fmi2Component c)
{
	component_ptr_t comp = (component_ptr_t)c;
	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {

		return fmi2OK;
	}
}

/* FMI 2.0 CS Functions */
const char* fmi_get_types_platform()
{
	return fmi2TypesPlatform;
}

fmi2Status fmi_reset(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi_set_real_input_derivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer order[], const fmi2Real value[])
{
    size_t k;

    return fmi2OK;
}

fmi2Status fmi_get_real_output_derivatives(fmi2Component c, const fmi2ValueReference vr[], size_t nvr, const fmi2Integer order[], fmi2Real value[])
{
	component_ptr_t comp	= (component_ptr_t)c;
	size_t k;

	for (k = 0; k < nvr; k++) 
    {
		value[k] = comp->output_real[vr[k]][order[k]];
	}

	return fmi2OK;
}

fmi2Status fmi_cancel_step(fmi2Component c)
{
	return fmi2OK;
}

fmi2Status fmi_do_step(fmi2Component c, fmi2Real currentCommunicationPoint, fmi2Real communicationStepSize, fmi2Boolean newStep)
{
	component_ptr_t comp	= (component_ptr_t)c;

	if (comp == NULL) 
    {
		return fmi2Fatal;
	} 
    else 
    {
		fmi2Real tstart = currentCommunicationPoint;
		fmi2Real tcur;
		fmi2Real tend = currentCommunicationPoint + communicationStepSize;
		fmi2Real hcur; 
		fmi2Real hdef = 0.01;	/* Default time step length */
		fmi2Real z_cur[N_EVENT_INDICATORS];
		fmi2Real z_pre[N_EVENT_INDICATORS];
		fmi2Real states[N_STATES];
		fmi2Real states_der[N_STATES];
		fmi2EventInfo eventInfo;
		fmi2Boolean callEventUpdate;
		fmi2Boolean terminateSimulation;
		fmi2Status fmi2Status;	
		size_t k;
		size_t counter = 0;

		fmi_get_continuous_states(comp, states, N_STATES);
		fmi_get_event_indicators(comp, z_pre, N_EVENT_INDICATORS);

		tcur = tstart;
		hcur = hdef;
		callEventUpdate = fmi2False;
		eventInfo = comp->eventInfo;

        takeStep(tend);

        fmi_set_time(comp, tend);
        
		for (k = 0; k < N_STATES; k++) 
        { /* Update states */
			comp->reals[k] = comp->states[k];
		}
		return fmi2OK;
	}
}

fmi2Status fmi_get_status(fmi2Component c, const fmi2StatusKind s, fmi2Status*  value)
{
	switch (s) 
    {
		case fmi2DoStepStatus:
			/* Return fmiPending if we are waiting. Otherwise the result from fmiDoStep */
			*value = fmi2OK;
			return fmi2OK;
		default: /* Not defined for status for this function */
			return fmi2Discard;
	}
}

fmi2Status fmi_get_real_status(fmi2Component c, const fmi2StatusKind s, fmi2Real*    value)
{
	switch (s) 
    {
		case fmi2LastSuccessfulTime:
			/* Return fmiPending if we are waiting. Otherwise return end time for last call to fmiDoStep */
			*value = 0.01;
			return fmi2OK;
		default: /* Not defined for status for this function */
			return fmi2Discard;
	}
}

fmi2Status fmi_get_integer_status(fmi2Component c, const fmi2StatusKind s, fmi2Integer* value)
{
	switch (s) 
    {
		default: /* Not defined for status for this function */
			return fmi2Discard;
	}
}

fmi2Status fmi_get_boolean_status(fmi2Component c, const fmi2StatusKind s, fmi2Boolean* value)
{
	switch (s) 
    {
		default: /* Not defined for status for this function */
			return fmi2Discard;
	}
}

fmi2Status fmi_get_string_status(fmi2Component c, const fmi2StatusKind s, fmi2String*  value)
{
	switch (s) 
    {
		case fmi2PendingStatus:
			*value = "Did fmi2DoStep really return with fmi2Pending? Then its time to implement this function";
			return fmi2Discard;
		default: /* Not defined for status for this function */
			return fmi2Discard;
	}
}
