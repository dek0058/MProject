/*****************************************************************//**
 * \file   ExceptionUtility.h
 * \brief  
 * 
  * \author dek0058
  * \date   2022-11-14
 *********************************************************************/
#pragma once

#define MEXCEPTION(Class, Name) Class(pTEXT(#Name), __LINE__, __FILE__)

#include "ExpiredException.h"
#include "NullException.h"

