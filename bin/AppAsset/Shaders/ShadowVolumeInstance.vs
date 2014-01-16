//////////////////////////////////////////////////////////////////////////////////////
//
//						The Bohge Engine License (BEL)
//
//	Copyright (c) 2011-2014 Peng Zhao
//
//	Permission is hereby granted, free of charge, to any person obtaining a copy
//	of this software and associated documentation files (the "Software"), to deal
//	in the Software without restriction, including without limitation the rights
//	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
//	copies of the Software, and to permit persons to whom the Software is
//	furnished to do so, subject to the following conditions:
//
//	The above copyright notice and this permission notice shall be included in 
//	all copies or substantial portions of the Software. And the logo of 
//	Bohge Engine shall be displayed full screen for more than 3 seconds 
//	when the software is started. Copyright holders are allowed to develop 
//	game edit based on Bohge Engine, The edit must be released under the MIT 
//	open source license if it is going to be published. In no event shall 
//	copyright holders be prohibited from using any code of Bohge Engine 
//	to develop any other analogous game engines.
//
//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//
//////////////////////////////////////////////////////////////////////////////////////



uniform vec3 g_vLightDirection;	// deng guang fang xiang
uniform mat4 g_matViewProj; //shi tu * tou ying

attribute vec4 g_vVertex;
attribute vec3 g_vNormal;
attribute vec4 matColum1;
attribute vec4 matColum2;
attribute vec4 matColum3;
attribute vec4 matColum4;


void main()
{
	mat3 NormalTransform = mat3( matColum1.xyz, matColum2.xyz, matColum3.xyz ) ;
	mat4 Transfrom = mat4( matColum1, matColum2, matColum3, matColum4 );
	
    vec3 vNormal = NormalTransform * g_vNormal;	

    if( dot( g_vLightDirection, vNormal ) < 0.0 )
    {
    	// jiang ding dian yan guang yuan fang xiang tou ying chu qu
        gl_Position = g_matViewProj * vec4( g_vLightDirection, 0.0 );
    }
    else
    {
        gl_Position = g_matViewProj * Transfrom * g_vVertex;
    }
}