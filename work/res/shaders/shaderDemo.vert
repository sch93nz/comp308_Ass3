//---------------------------------------------------------------------------
//
// Copyright (c) 2015 Taehyun Rhee, Joshua Scott, Ben Allen
//
// This software is provided 'as-is' for assignment of COMP308 in ECS,
// Victoria University of Wellington, without any express or implied warranty. 
// In no event will the authors be held liable for any damages arising from
// the use of this software.
//
// The contents of this file may not be copied or duplicated in any form
// without the prior permission of its owner.
//
//----------------------------------------------------------------------------

#version 120

// Values to pass to the fragment shader
//varying vec3 vNormal;
//varying vec3 vPosition;
//varying vec2 vTextureCoord0;

//void main() {
//	vNormal = normalize(gl_NormalMatrix * gl_Normal);
//	vPosition = vec3(gl_ModelViewMatrix * gl_Vertex);
//	vTextureCoord0 = gl_MultiTexCoord0.xy;
//	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
//}

// i got this off the internet i was hoping to  use it to figure out how everything
//worked but i didn't not get to the point of implementing anything of my own.
varying vec3 N;
varying vec3 v;
varying vec2 vTextureCoord0;
void main(void)  
{     
   v = vec3(gl_ModelViewMatrix * gl_Vertex);       
   N = normalize(gl_NormalMatrix * gl_Normal);
   vTextureCoord0 = gl_MultiTexCoord0.xy;
   gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  
}