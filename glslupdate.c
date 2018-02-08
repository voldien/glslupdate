#include"glslupdate.h"
#include<stdio.h>
#include<string.h>
#include<malloc.h>
#include<assert.h>

#ifdef GL_ES_VERSION_3_0
	#include<GLES3/gl3.h>
	#include<GLES3/gl3ext.h>
	#include<GLES3/gl3platform.h>
#elif defined(GL_ES_VERSION_2_0)
	#include<GLES2/gl2.h>
	#include<GLES2/gl2ext.h>
	#include<GLES2/gl2platform.h>
#elif defined(GL_ES_VERSION_1_0)
	#include<GLES/gl.h>
	#include<GLES/glext.h>
	#include<GLES/glplatform.h>
#else
	#include<GL/gl.h>
	#include<GL/glext.h>
#endif

unsigned int glupCopyGLSLUniform(UniformAllocationCollection* collection,
        unsigned int program) {

	unsigned int i,j;
	int array;
	unsigned int uni_type;
	GLsizei len;
	GLint numUniform;
	int size;
	const GLsizei bufsize = sizeof(collection->uniform_all->name);

	assert(collection);

	/*	Cleanup memory.	*/
	memset(collection, 0, sizeof(UniformAllocationCollection));

	/*	Get all uniform assoicated with shader program.	*/
	glGetProgramiv(program, GL_ACTIVE_UNIFORMS, &numUniform);
	if(!numUniform)
		return 0;	/*error nothing was copied*/

	/*	Allocate memory for each uniform.	*/
	collection->numUniform = numUniform;
	collection->uniform_all = (UniformAllocation*)malloc(sizeof(*collection) * numUniform);

	/*	Iterate through each uniform.	*/
	for(i = 0; i < numUniform;i++){
		glGetActiveUniform(program, i, bufsize, &len, &array, &uni_type,
		        (char*) collection->uniform_all[i].name);

		/*	Failed extracting.	*/
		if(!len)
			continue;

		/*	Compute the size of the uniform variable size.	*/
		size = glupGetGLSLTypeSize(uni_type);
		collection->uniform_all[i].uniform_type = uni_type;
		collection->uniform_all[i].index = i;
		collection->uniform_all[i].size = size;
		collection->uniform_all[i].Array = array;

		switch(uni_type){
			case GL_FLOAT_VEC2:
			case GL_FLOAT_VEC3:
			case GL_FLOAT_VEC4:
			case GL_FLOAT:
			case GL_FLOAT_MAT3:
			case GL_FLOAT_MAT4:
			case GL_FLOAT_MAT2:
			case GL_FLOAT_MAT2x3:
			if(array < 2){
				glGetUniformfv(program, i, (float*)collection->uniform_all[i].data);
			}
			else{
				for(j = 0; j < array; j++){
					glGetUniformfv(program, i++,(float*)(collection->uniform_all[i].data + j));
					continue;
				}
			}
			break;
			case GL_INT_VEC2:
			case GL_INT_VEC3:
			case GL_INT_VEC4:
			case GL_INT:
			case GL_SAMPLER_2D:
			case GL_UNSIGNED_INT:
			case GL_SAMPLER_CUBE:
			case GL_SAMPLER_1D_SHADOW:
			case GL_SAMPLER_2D_SHADOW:
			case GL_SAMPLER_1D_ARRAY:
			case GL_SAMPLER_2D_ARRAY:
			case GL_SAMPLER_1D_ARRAY_SHADOW:
			case GL_SAMPLER_2D_ARRAY_SHADOW:
			case GL_SAMPLER_2D_MULTISAMPLE:
			case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
			case GL_SAMPLER_CUBE_SHADOW	:
			case GL_SAMPLER_BUFFER:
			case GL_SAMPLER_2D_RECT:
			case GL_SAMPLER_2D_RECT_SHADOW:
			case GL_INT_SAMPLER_1D:
			case GL_INT_SAMPLER_2D:
			case GL_INT_SAMPLER_3D:
			case GL_INT_SAMPLER_CUBE:
			case GL_INT_SAMPLER_1D_ARRAY:
			case GL_INT_SAMPLER_2D_ARRAY:
			case GL_INT_SAMPLER_2D_MULTISAMPLE:
			case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
			case GL_INT_SAMPLER_BUFFER:
			case GL_INT_SAMPLER_2D_RECT:
			case GL_UNSIGNED_INT_SAMPLER_1D:
			case GL_UNSIGNED_INT_SAMPLER_2D:
			case GL_UNSIGNED_INT_SAMPLER_3D:
			case GL_UNSIGNED_INT_SAMPLER_CUBE:
			case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
			case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
			case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
			case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
			case GL_UNSIGNED_INT_SAMPLER_BUFFER	:
			case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
			case GL_IMAGE_1D:
			case GL_IMAGE_2D:
			case GL_IMAGE_3D:
			case GL_IMAGE_2D_RECT:
			case GL_IMAGE_CUBE:
			case GL_IMAGE_BUFFER:
			case GL_IMAGE_1D_ARRAY:
			case GL_IMAGE_2D_ARRAY:
			case GL_IMAGE_2D_MULTISAMPLE:
			case GL_IMAGE_2D_MULTISAMPLE_ARRAY:
			case GL_INT_IMAGE_1D:
			case GL_INT_IMAGE_2D:
			case GL_INT_IMAGE_3D:
			case GL_INT_IMAGE_2D_RECT:
			case GL_INT_IMAGE_CUBE:
			case GL_INT_IMAGE_BUFFER:
			case GL_INT_IMAGE_1D_ARRAY:
			case GL_INT_IMAGE_2D_ARRAY:
			case GL_INT_IMAGE_2D_MULTISAMPLE:
			case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
			case GL_UNSIGNED_INT_IMAGE_1D:
			case GL_UNSIGNED_INT_IMAGE_2D:
			case GL_UNSIGNED_INT_IMAGE_3D:
			case GL_UNSIGNED_INT_IMAGE_2D_RECT:
			case GL_UNSIGNED_INT_IMAGE_CUBE:
			case GL_UNSIGNED_INT_IMAGE_BUFFER:
			case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:
			case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:
			case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
			case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
			case GL_UNSIGNED_INT_ATOMIC_COUNTER:
			case GL_SAMPLER_1D:
			case GL_SAMPLER_3D:

			if(array < 2){
				glGetUniformiv(program, i, (int*)collection->uniform_all[i].data);
			}
			else{
				for(j = 0; j < array; j++){
					glGetUniformiv(program, i + j,(int*)(collection->uniform_all[i].data + j));
					continue;
				}
			}
			break;
			case GL_DOUBLE_MAT2:
			if(array < 2){
				glGetUniformdv(program, i, (double*)collection->uniform_all[i].data);
			}
			else{
				for(j = 0; j < array; j++){
					glGetUniformdv(program, i++,(double*)(collection->uniform_all[i].data + j));
					continue;
				}
			}
				break;
			default:
				break;
		} /* type	*/
	} /* active uniform	*/

	/*	Success.	*/
	return 1;
}

unsigned int glupPastGLSLUniform(const UniformAllocationCollection* collection, unsigned int program){

	unsigned int i;

	for (i = 0; i < collection->numUniform; i++) {
		switch (collection->uniform_all[i].uniform_type) {
		case GL_BOOL:
		case GL_BOOL_VEC2:
		case GL_BOOL_VEC3:
		case GL_BOOL_VEC4:
		case GL_FLOAT:
			glProgramUniform1fv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (float*) collection->uniform_all[i].data);
			break;
		case GL_INT:
		case GL_SAMPLER_CUBE:
		case GL_SAMPLER_1D_SHADOW:
		case GL_SAMPLER_2D_SHADOW:
		case GL_SAMPLER_1D_ARRAY:
		case GL_SAMPLER_2D_ARRAY:
		case GL_SAMPLER_1D_ARRAY_SHADOW:
		case GL_SAMPLER_2D_ARRAY_SHADOW:
		case GL_SAMPLER_2D_MULTISAMPLE:
		case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
		case GL_SAMPLER_CUBE_SHADOW:
		case GL_SAMPLER_BUFFER:
		case GL_SAMPLER_2D_RECT:
		case GL_SAMPLER_2D_RECT_SHADOW:
		case GL_INT_SAMPLER_1D:
		case GL_INT_SAMPLER_2D:
		case GL_INT_SAMPLER_3D:
		case GL_INT_SAMPLER_CUBE:
		case GL_INT_SAMPLER_1D_ARRAY:
		case GL_INT_SAMPLER_2D_ARRAY:
		case GL_INT_SAMPLER_2D_MULTISAMPLE:
		case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
		case GL_INT_SAMPLER_BUFFER:
		case GL_INT_SAMPLER_2D_RECT:
		case GL_UNSIGNED_INT_SAMPLER_1D:
		case GL_UNSIGNED_INT_SAMPLER_2D:
		case GL_UNSIGNED_INT_SAMPLER_3D:
		case GL_UNSIGNED_INT_SAMPLER_CUBE:
		case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
		case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
		case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
		case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
		case GL_UNSIGNED_INT_SAMPLER_BUFFER:
		case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
		case GL_IMAGE_1D:
		case GL_IMAGE_2D:
		case GL_IMAGE_3D:
		case GL_IMAGE_2D_RECT:
		case GL_IMAGE_CUBE:
		case GL_IMAGE_BUFFER:
		case GL_IMAGE_1D_ARRAY:
		case GL_IMAGE_2D_ARRAY:
		case GL_IMAGE_2D_MULTISAMPLE:
		case GL_IMAGE_2D_MULTISAMPLE_ARRAY:
		case GL_INT_IMAGE_1D:
		case GL_INT_IMAGE_2D:
		case GL_INT_IMAGE_3D:
		case GL_INT_IMAGE_2D_RECT:
		case GL_INT_IMAGE_CUBE:
		case GL_INT_IMAGE_BUFFER:
		case GL_INT_IMAGE_1D_ARRAY:
		case GL_INT_IMAGE_2D_ARRAY:
		case GL_INT_IMAGE_2D_MULTISAMPLE:
		case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
		case GL_UNSIGNED_INT_IMAGE_1D:
		case GL_UNSIGNED_INT_IMAGE_2D:
		case GL_UNSIGNED_INT_IMAGE_3D:
		case GL_UNSIGNED_INT_IMAGE_2D_RECT:
		case GL_UNSIGNED_INT_IMAGE_CUBE:
		case GL_UNSIGNED_INT_IMAGE_BUFFER:
		case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:
		case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:
		case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
		case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
		case GL_UNSIGNED_INT_ATOMIC_COUNTER:
		case GL_SAMPLER_1D:
		case GL_SAMPLER_2D:
		case GL_SAMPLER_3D:
			glProgramUniform1iv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (int*) collection->uniform_all[i].data);
			break;
		case GL_DOUBLE:
			glProgramUniform1dv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (double*) collection->uniform_all[i].data);
			break;
		case GL_FLOAT_VEC2:
			glProgramUniform2fv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (float*) collection->uniform_all[i].data);
			break;
		case GL_INT_VEC2:
			glProgramUniform2iv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (int*) collection->uniform_all[i].data);
			break;
		case GL_DOUBLE_VEC2:
			glProgramUniform2dv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (double*) collection->uniform_all[i].data);
			break;
		case GL_FLOAT_VEC3:
			glProgramUniform2fv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (float*) collection->uniform_all[i].data);
			break;
		case GL_INT_VEC3:
			glProgramUniform2iv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (int*) collection->uniform_all[i].data);
			break;
		case GL_DOUBLE_VEC3:
			glProgramUniform2dv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (double*) collection->uniform_all[i].data);
			break;
		case GL_FLOAT_VEC4:
			glProgramUniform4fv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (float*) collection->uniform_all[i].data);
			break;
		case GL_INT_VEC4:
			glProgramUniform4iv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (int*) collection->uniform_all[i].data);
			break;
		case GL_DOUBLE_VEC4:
			glProgramUniform4dv(program, collection->uniform_all[i].index,
			        collection->uniform_all[i].Array,
			        (double*) collection->uniform_all[i].data);
			break;
		case GL_FLOAT_MAT2:
			glProgramUniformMatrix2fv(program,
			        collection->uniform_all[i].index,
			        collection->uniform_all[i].Array, GL_TRUE,
			        (float*) collection->uniform_all[i].data);
			break;
		case GL_FLOAT_MAT3:
			glProgramUniformMatrix3fv(program,
			        collection->uniform_all[i].index,
			        collection->uniform_all[i].Array, GL_TRUE,
			        (float*) collection->uniform_all[i].data);
			break;
		case GL_FLOAT_MAT4:
			glProgramUniformMatrix4fv(program,
			        collection->uniform_all[i].index,
			        collection->uniform_all[i].Array, GL_TRUE,
			        (float*) collection->uniform_all[i].data);
			break;
		default:
			continue;

		}
	}/*collection number*/

	/*	Success.	*/
	return 1;
}

unsigned int glupGetGLSLTypeSize(unsigned int type) {
	switch (type) {
	case GL_FLOAT:
		return sizeof(GLfloat);
	case GL_FLOAT_VEC2:
		return sizeof(GLfloat) * 2;
	case GL_FLOAT_VEC3:
		return sizeof(GLfloat) * 3;
	case GL_FLOAT_VEC4:
		return sizeof(GLfloat) * 4;
	case GL_DOUBLE:
		return sizeof(GLdouble);
	case GL_DOUBLE_VEC2:
		return sizeof(GLdouble) * 2;
	case GL_DOUBLE_VEC3:
		return sizeof(GLdouble) * 3;
	case GL_DOUBLE_VEC4:
		return sizeof(GLdouble) * 4;
	case GL_INT:
		return sizeof(GLint);
	case GL_INT_VEC2:
		return sizeof(GLfloat) * 2;
	case GL_INT_VEC3:
		return sizeof(GLfloat) * 3;
	case GL_INT_VEC4:
		return sizeof(GLfloat) * 4;
	case GL_UNSIGNED_INT:
		return sizeof(GLuint);
	case GL_UNSIGNED_INT_VEC2:
		return sizeof(GLuint) * 2;
	case GL_UNSIGNED_INT_VEC3:
		return sizeof(GLuint) * 3;
	case GL_UNSIGNED_INT_VEC4:
		return sizeof(GLuint) * 4;
	case GL_BOOL:
		return sizeof(GLboolean);
	case GL_BOOL_VEC2:
		return sizeof(GLboolean) * 2;
	case GL_BOOL_VEC3:
		return sizeof(GLboolean) * 3;
	case GL_BOOL_VEC4:
		return sizeof(GLboolean) * 4;
	case GL_FLOAT_MAT2:
		return sizeof(GLfloat) * 4;
	case GL_FLOAT_MAT3:
		return sizeof(GLfloat) * 9;
	case GL_FLOAT_MAT4:
		return sizeof(GLfloat) * 16;
	case GL_FLOAT_MAT2x3:
		return sizeof(GLfloat) * 6;
	case GL_FLOAT_MAT2x4:
		return sizeof(GLfloat) * 4;
	case GL_FLOAT_MAT3x2:
		return sizeof(GLfloat) * 6;
	case GL_FLOAT_MAT3x4:
		return sizeof(GLfloat) * 12;
	case GL_FLOAT_MAT4x2:
		return sizeof(GLfloat) * 8;
	case GL_FLOAT_MAT4x3:
		return sizeof(GLfloat) * 12;
	case GL_DOUBLE_MAT2:
		return sizeof(GLdouble) * 4;
	case GL_DOUBLE_MAT3:
		return sizeof(GLdouble) * 9;
	case GL_DOUBLE_MAT4:
		return sizeof(GLdouble) * 16;
	case GL_DOUBLE_MAT2x3:
		return sizeof(GLdouble) * 6;
	case GL_DOUBLE_MAT2x4:
		return sizeof(GLdouble) * 8;
	case GL_DOUBLE_MAT3x2:
		return sizeof(GLdouble) * 6;
	case GL_DOUBLE_MAT3x4:
		return sizeof(GLdouble) * 12;
	case GL_DOUBLE_MAT4x2:
		return sizeof(GLdouble) * 8;
	case GL_DOUBLE_MAT4x3:
		return sizeof(GLdouble) * 12;
	case GL_SAMPLER_1D:
	case GL_SAMPLER_2D:
	case GL_SAMPLER_3D:
		return sizeof(GLuint);
	case GL_SAMPLER_CUBE:
	case GL_SAMPLER_1D_SHADOW:
	case GL_SAMPLER_2D_SHADOW:
	case GL_SAMPLER_1D_ARRAY:
	case GL_SAMPLER_2D_ARRAY:
	case GL_SAMPLER_1D_ARRAY_SHADOW:
	case GL_SAMPLER_2D_ARRAY_SHADOW:
	case GL_SAMPLER_2D_MULTISAMPLE:
	case GL_SAMPLER_2D_MULTISAMPLE_ARRAY:
	case GL_SAMPLER_CUBE_SHADOW:
	case GL_SAMPLER_BUFFER:
	case GL_SAMPLER_2D_RECT:
	case GL_SAMPLER_2D_RECT_SHADOW:
	case GL_INT_SAMPLER_1D:
	case GL_INT_SAMPLER_2D:
	case GL_INT_SAMPLER_3D:
	case GL_INT_SAMPLER_CUBE:
	case GL_INT_SAMPLER_1D_ARRAY:
	case GL_INT_SAMPLER_2D_ARRAY:
	case GL_INT_SAMPLER_2D_MULTISAMPLE:
	case GL_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
	case GL_INT_SAMPLER_BUFFER:
	case GL_INT_SAMPLER_2D_RECT:
	case GL_UNSIGNED_INT_SAMPLER_1D:
	case GL_UNSIGNED_INT_SAMPLER_2D:
	case GL_UNSIGNED_INT_SAMPLER_3D:
	case GL_UNSIGNED_INT_SAMPLER_CUBE:
	case GL_UNSIGNED_INT_SAMPLER_1D_ARRAY:
	case GL_UNSIGNED_INT_SAMPLER_2D_ARRAY:
	case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE:
	case GL_UNSIGNED_INT_SAMPLER_2D_MULTISAMPLE_ARRAY:
	case GL_UNSIGNED_INT_SAMPLER_BUFFER:
	case GL_UNSIGNED_INT_SAMPLER_2D_RECT:
	case GL_IMAGE_1D:
	case GL_IMAGE_2D:
	case GL_IMAGE_3D:
	case GL_IMAGE_2D_RECT:
	case GL_IMAGE_CUBE:
	case GL_IMAGE_BUFFER:
	case GL_IMAGE_1D_ARRAY:
	case GL_IMAGE_2D_ARRAY:
	case GL_IMAGE_2D_MULTISAMPLE:
	case GL_IMAGE_2D_MULTISAMPLE_ARRAY:
	case GL_INT_IMAGE_1D:
	case GL_INT_IMAGE_2D:
	case GL_INT_IMAGE_3D:
	case GL_INT_IMAGE_2D_RECT:
	case GL_INT_IMAGE_CUBE:
	case GL_INT_IMAGE_BUFFER:
	case GL_INT_IMAGE_1D_ARRAY:
	case GL_INT_IMAGE_2D_ARRAY:
	case GL_INT_IMAGE_2D_MULTISAMPLE:
	case GL_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
	case GL_UNSIGNED_INT_IMAGE_1D:
	case GL_UNSIGNED_INT_IMAGE_2D:
	case GL_UNSIGNED_INT_IMAGE_3D:
	case GL_UNSIGNED_INT_IMAGE_2D_RECT:
	case GL_UNSIGNED_INT_IMAGE_CUBE:
	case GL_UNSIGNED_INT_IMAGE_BUFFER:
	case GL_UNSIGNED_INT_IMAGE_1D_ARRAY:
	case GL_UNSIGNED_INT_IMAGE_2D_ARRAY:
	case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE:
	case GL_UNSIGNED_INT_IMAGE_2D_MULTISAMPLE_ARRAY:
	case GL_UNSIGNED_INT_ATOMIC_COUNTER:
		return sizeof(GLint);
	default:
		return 0;
	}
}

void glupFreeGLSLUnicoll(UniformAllocationCollection* collection){

	assert(collection);
	free(collection->uniform_all);
}
