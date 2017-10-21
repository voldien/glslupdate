/**
	Copy current glsl uniform state and paste.
	Copyright (C) 2014  Valdemar Lindberg

	This program is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	This program is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with this program.  If not, see <http://www.gnu.org/licenses/>.

*/
#ifndef _GLSL_UPDATE_H_
#define _GLSL_UPDATE_H_ 1
#include<stdio.h>

/**
 *
 */
#define GLUPDECLSPEC
#define GLUAPIENTRY

#ifdef __cplusplus  /*	C++ environment	*/
extern "C"{
#endif

/**
 * 	Uniform allocation block.
 */
typedef struct uniform_allocation_t{
	unsigned int uniform_type;			/*	Data Type	*/
	unsigned int size;				/*	size	*/
	unsigned int index;				/*	Index Uniform Location	*/
	unsigned int Array;				/*	Array	*/
	char name[64];					/*	name	*/
	unsigned int data[32];				/*	data	*/
}UniformAllocation;

/**
 *	Collection of uniform.
 */
typedef struct uniform_allocation_collection_t{
	unsigned int numUniform;                    /*	*/
	UniformAllocation* uniform_all;     		/*	*/
}UniformAllocationCollection;

/**
 *	Copy glsl uniform state of
 *	glsl program.
 *
 *	\collection non zero pointer of uniform
 *	allocation collection.
 *
 *	\program valid glsl program.
 *
 *	@Return non-zero if successfully.
 */
extern GLUPDECLSPEC unsigned int GLUAPIENTRY glupCopyGLSLUniform(
        UniformAllocationCollection* collection, unsigned int program);

/**
 *	Past glsl uniform state to program.
 *	This is by iterating through each matching
 *	uniform in shader and uniform allocation
 *	collection object.
 *
 *	\collection
 *
 *	\program valid glsl shader program.
 *
 *	@Return zero if successfully.
 */
extern GLUPDECLSPEC unsigned int GLUAPIENTRY glupPastGLSLUniform(
        const UniformAllocationCollection* collection, unsigned int program);

/**
 *	Get glsl type size in bytes.
 *
 *	\type OpenGL enumerator representing
 *	data type, like GL_FLOAT.
 *
 *	@Return size of data type.
 */
extern GLUPDECLSPEC unsigned int GLUAPIENTRY glupGetGLSLTypeSize(
        unsigned int type);

/**
 *   Free resources from uniform allocation buffer.
 *
 *   @Return
 */
extern GLUPDECLSPEC void GLUAPIENTRY glupFreeGLSLUnicoll(
        UniformAllocationCollection* collection);

#ifdef __cplusplus  /*	C++ environment	*/
}
#endif

#endif
