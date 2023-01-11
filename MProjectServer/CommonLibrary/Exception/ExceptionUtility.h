/*****************************************************************//**
 * \file   ExceptionUtility.h
 * \brief  
 * 
  * \author dek0058
  * \date   2023-01-11
 *********************************************************************/
#pragma once

#define MEXCEPTION(Class, Name) Class(pTEXT(#Name), __LINE__, __FILE__)
#define MEXCEPTION_Param1(Class, Name, Param1) Class(pTEXT(#Name), pTEXT(#Param1), __LINE__, __FILE__)

#include "DuplicateException.h"
#include "ExpiredException.h"
#include "NotFoundException.h"
#include "NullException.h"
