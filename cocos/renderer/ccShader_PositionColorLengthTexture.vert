/* Copyright (c) 2012 Scott Lembcke and Howling Moon Software
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

const char* ccPositionColorLengthTexture_vert = R"(

#ifdef GL_ES
attribute highp vec4 a_position;
attribute highp vec2 a_texcoord;
attribute lowp vec4 a_color;
#else
attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec4 a_color;
#endif

#ifdef GL_ES
varying lowp vec4 v_color;
varying highp vec2 v_texcoord;
uniform lowp float u_alpha;
#else
varying vec4 v_color;
varying vec2 v_texcoord;
uniform float u_alpha;
#endif

void main()
{
    v_color = vec4(a_color.rgb * a_color.a * u_alpha, a_color.a * u_alpha);
    v_texcoord = a_texcoord;

    gl_Position = CC_MVPMatrix * a_position;
}
)";
