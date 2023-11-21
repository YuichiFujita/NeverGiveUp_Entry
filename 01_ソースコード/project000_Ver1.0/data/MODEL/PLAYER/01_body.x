xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 273;
 4.04558;29.98782;-4.25131;,
 6.04397;30.74365;-1.61661;,
 7.92830;29.68658;-2.27346;,
 5.44684;28.56497;-5.08826;,
 0.00000;28.20671;-6.23000;,
 0.00000;29.41071;-5.50900;,
 4.67442;30.61782;0.80888;,
 0.00000;29.39671;2.90500;,
 6.00051;28.97594;1.90508;,
 7.29316;29.73684;0.11879;,
 0.00000;27.67821;4.03200;,
 3.90208;28.31318;3.34859;,
 2.81946;33.19369;-3.45450;,
 0.00000;32.91071;-4.66900;,
 0.00000;33.72621;-3.20950;,
 2.05845;33.82008;-2.72072;,
 2.55454;34.07026;-0.91126;,
 4.07617;33.58250;-0.96376;,
 0.00000;34.03775;-0.94850;,
 0.00000;31.22374;-5.20450;,
 3.18216;31.69652;-3.78339;,
 5.11584;32.21085;-1.25153;,
 3.22175;32.07008;1.28096;,
 0.00000;31.77675;2.42900;,
 2.79723;33.52727;1.21212;,
 0.00000;33.39724;2.12100;,
 2.04274;34.06218;0.67305;,
 0.00000;34.02721;1.03250;,
 -5.44684;28.56497;-5.08826;,
 -7.92830;29.68658;-2.27346;,
 -6.04397;30.74365;-1.61661;,
 -4.04558;29.98782;-4.25131;,
 -7.29316;29.73684;0.11879;,
 -6.00051;28.97594;1.90508;,
 -4.67442;30.61782;0.80888;,
 -3.90208;28.31318;3.34859;,
 -2.05845;33.82008;-2.72072;,
 -2.81946;33.19369;-3.45450;,
 -4.07617;33.58250;-0.96376;,
 -2.55454;34.07026;-0.91126;,
 -3.18216;31.69652;-3.78339;,
 -5.11584;32.21085;-1.25153;,
 -3.22175;32.07008;1.28096;,
 -2.79723;33.52727;1.21212;,
 -2.04274;34.06218;0.67305;,
 0.00000;12.29571;5.48100;,
 0.00000;7.27454;6.42985;,
 4.74523;7.73066;6.09766;,
 4.41773;12.75900;5.20020;,
 4.71383;18.19048;5.14444;,
 0.00000;17.74871;5.38300;,
 8.11482;13.81082;4.20795;,
 9.58321;19.45545;4.00036;,
 8.78255;8.06445;4.71548;,
 11.35711;28.37849;-2.91301;,
 10.00779;27.40034;-5.05708;,
 4.87938;26.15214;-7.06471;,
 0.00000;26.24321;-7.64050;,
 8.70068;25.52935;-6.51966;,
 8.18618;13.02567;-7.07613;,
 9.45322;6.77260;-7.98682;,
 5.23614;6.73267;-9.43953;,
 4.78706;12.61540;-8.83470;,
 4.62710;18.60856;-8.13172;,
 8.76295;19.45475;-6.61854;,
 0.00000;12.57221;-9.22600;,
 0.00000;18.35771;-8.65900;,
 0.00000;6.62256;-9.81561;,
 11.27063;27.98100;0.70203;,
 11.54276;28.48150;-0.95578;,
 11.37122;7.28508;1.97043;,
 10.24324;3.71206;5.70808;,
 12.61116;2.89653;2.75821;,
 13.52169;2.62696;-1.18895;,
 12.43442;6.40048;-1.53982;,
 10.48428;3.04707;-8.26896;,
 5.83723;2.45497;-9.79034;,
 0.00000;2.01036;-10.15164;,
 11.82031;6.46576;-5.08228;,
 12.92567;2.96300;-5.10044;,
 13.95579;26.41877;-3.20890;,
 14.02947;26.69565;-0.81172;,
 10.77755;12.89694;-1.01038;,
 10.13572;13.53961;1.95314;,
 10.71997;18.25768;1.91758;,
 10.73726;17.96270;-0.84424;,
 10.09529;12.91692;-4.22293;,
 9.95169;18.01513;-3.43987;,
 10.94058;24.28849;-6.39373;,
 12.56423;25.42351;-5.19134;,
 0.00000;4.19783;7.60098;,
 5.60696;4.22236;7.21382;,
 5.30215;25.85009;4.39295;,
 10.06586;25.71706;3.56895;,
 10.79806;27.27256;2.17752;,
 0.00000;25.69371;4.87900;,
 0.00000;22.99871;-8.27750;,
 4.68667;22.93942;-7.83814;,
 8.08888;22.97775;-7.09124;,
 9.17417;23.08352;4.37395;,
 5.00426;22.67688;4.93594;,
 0.00000;22.33021;5.27100;,
 0.00000;0.75877;8.98391;,
 0.00000;0.61107;8.39696;,
 5.47253;0.36995;7.95368;,
 5.54568;0.44163;8.61333;,
 10.90673;-0.78190;5.85648;,
 11.29233;-0.68257;6.50934;,
 13.73214;-0.16558;-5.22795;,
 11.24455;0.08694;-8.42723;,
 11.67897;-0.05918;-9.35637;,
 14.41632;-0.26264;-5.82172;,
 15.06040;-0.72887;-1.39398;,
 14.31944;-0.64481;-1.19945;,
 6.15555;-0.20317;-9.83822;,
 0.00000;-0.40092;-10.25699;,
 0.00000;-0.49808;-11.17420;,
 6.06770;-0.33554;-10.80870;,
 13.51616;-0.90860;3.11734;,
 14.17171;-0.92061;3.34971;,
 13.64818;26.41765;0.91263;,
 13.28481;26.10583;1.96598;,
 12.64078;25.25345;3.06331;,
 9.88988;23.28015;-6.61360;,
 11.47377;23.36771;3.81773;,
 10.93806;20.81271;3.00671;,
 10.08857;20.97882;-5.02673;,
 11.20742;20.07642;-0.32469;,
 11.13717;20.07673;-1.35506;,
 10.72729;21.71932;-4.31561;,
 11.46296;21.70458;2.08082;,
 11.75846;22.19073;-1.86592;,
 11.89895;22.19018;0.19484;,
 12.82627;24.30389;0.55374;,
 12.90985;24.30473;-2.53739;,
 11.75576;23.57141;-4.75349;,
 12.42797;23.90521;2.02338;,
 10.94058;24.28849;-6.39373;,
 9.88988;23.28015;-6.61360;,
 8.70068;25.52935;-6.51966;,
 8.08888;22.97775;-7.09124;,
 8.70068;25.52935;-6.51966;,
 9.88988;23.28015;-6.61360;,
 -4.41773;12.75900;5.20020;,
 -4.74523;7.73066;6.09766;,
 -4.71383;18.19048;5.14444;,
 -9.58321;19.45545;4.00036;,
 -8.11482;13.81082;4.20795;,
 -8.78255;8.06445;4.71548;,
 -10.00779;27.40034;-5.05708;,
 -11.35711;28.37849;-2.91301;,
 -4.87938;26.15214;-7.06471;,
 -8.70068;25.52935;-6.51966;,
 -4.78706;12.61540;-8.83470;,
 -5.23614;6.73267;-9.43953;,
 -9.45322;6.77260;-7.98682;,
 -8.18618;13.02567;-7.07613;,
 -8.76295;19.45475;-6.61854;,
 -4.62710;18.60856;-8.13172;,
 -11.54276;28.48150;-0.95578;,
 -11.27063;27.98100;0.70203;,
 -12.61116;2.89653;2.75821;,
 -10.24324;3.71206;5.70808;,
 -11.37122;7.28508;1.97043;,
 -12.43442;6.40048;-1.53982;,
 -13.52169;2.62696;-1.18895;,
 -5.83723;2.45497;-9.79034;,
 -10.48428;3.04707;-8.26896;,
 -12.92567;2.96300;-5.10044;,
 -11.82031;6.46576;-5.08228;,
 -14.02947;26.69565;-0.81172;,
 -13.95579;26.41877;-3.20890;,
 -10.13572;13.53961;1.95314;,
 -10.77755;12.89694;-1.01038;,
 -10.71997;18.25768;1.91758;,
 -10.73726;17.96270;-0.84424;,
 -10.09529;12.91692;-4.22293;,
 -9.95169;18.01513;-3.43987;,
 -12.56423;25.42351;-5.19134;,
 -10.94058;24.28849;-6.39373;,
 -5.60696;4.22236;7.21382;,
 -10.79806;27.27256;2.17752;,
 -10.06586;25.71706;3.56895;,
 -5.30215;25.85009;4.39295;,
 -4.68667;22.93942;-7.83814;,
 -8.08888;22.97775;-7.09124;,
 -5.00426;22.67688;4.93594;,
 -9.17417;23.08352;4.37395;,
 -5.54568;0.44163;8.61333;,
 -5.47253;0.36995;7.95368;,
 -11.29233;-0.68257;6.50934;,
 -10.90673;-0.78190;5.85648;,
 -14.41632;-0.26264;-5.82172;,
 -11.67897;-0.05918;-9.35637;,
 -11.24455;0.08694;-8.42723;,
 -13.73214;-0.16558;-5.22795;,
 -14.31944;-0.64481;-1.19945;,
 -15.06040;-0.72887;-1.39398;,
 -6.06770;-0.33554;-10.80870;,
 -6.15555;-0.20317;-9.83822;,
 -14.17171;-0.92061;3.34971;,
 -13.51616;-0.90860;3.11734;,
 -13.28481;26.10583;1.96598;,
 -13.64818;26.41765;0.91263;,
 -12.64078;25.25345;3.06331;,
 -9.88988;23.28015;-6.61360;,
 -11.47377;23.36771;3.81773;,
 -10.93806;20.81271;3.00671;,
 -10.08857;20.97882;-5.02673;,
 -11.13717;20.07673;-1.35506;,
 -11.20742;20.07642;-0.32469;,
 -10.72729;21.71932;-4.31561;,
 -11.46296;21.70458;2.08082;,
 -11.89895;22.19018;0.19484;,
 -11.75846;22.19073;-1.86592;,
 -12.82627;24.30389;0.55374;,
 -12.90985;24.30473;-2.53739;,
 -11.75576;23.57141;-4.75349;,
 -12.42797;23.90521;2.02338;,
 -8.70068;25.52935;-6.51966;,
 -9.88988;23.28015;-6.61360;,
 -10.94058;24.28849;-6.39373;,
 -8.08888;22.97775;-7.09124;,
 0.00000;1.08143;-6.47664;,
 -3.09879;1.08143;-6.06099;,
 -6.15555;-0.20317;-9.83822;,
 0.00000;-0.40092;-10.25699;,
 -5.72586;1.08143;-4.87728;,
 -11.24455;0.08694;-8.42723;,
 -7.48118;1.08143;-3.10576;,
 -13.73214;-0.16558;-5.22795;,
 -8.09760;1.08143;-1.01608;,
 -14.31944;-0.64481;-1.19945;,
 -7.48118;1.08143;1.07359;,
 -13.51616;-0.90860;3.11734;,
 -5.72586;1.08143;2.84511;,
 -10.90673;-0.78190;5.85648;,
 -3.09879;1.08143;4.02881;,
 -5.47253;0.36995;7.95368;,
 0.00000;1.08143;4.44447;,
 0.00000;0.61107;8.39696;,
 3.09879;1.08143;4.02881;,
 5.47253;0.36995;7.95368;,
 5.72586;1.08143;2.84511;,
 10.90673;-0.78190;5.85648;,
 7.48118;1.08143;1.07359;,
 13.51616;-0.90860;3.11734;,
 8.09760;1.08143;-1.01608;,
 14.31944;-0.64481;-1.19945;,
 7.48118;1.08143;-3.10576;,
 13.73214;-0.16558;-5.22795;,
 5.72586;1.08143;-4.87728;,
 11.24455;0.08694;-8.42723;,
 3.09879;1.08143;-6.06099;,
 6.15555;-0.20317;-9.83822;,
 0.00000;1.08143;-6.47664;,
 0.00000;-0.40092;-10.25699;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;,
 0.00000;2.16951;-1.01608;;
 
 260;
 4;0,1,2,3;,
 4;4,5,0,3;,
 4;6,7,8,9;,
 4;2,1,6,9;,
 4;8,7,10,11;,
 4;12,13,14,15;,
 4;16,17,12,15;,
 4;14,18,16,15;,
 4;0,5,19,20;,
 4;21,1,0,20;,
 4;12,17,21,20;,
 4;19,13,12,20;,
 4;6,1,21,22;,
 4;23,7,6,22;,
 4;24,25,23,22;,
 4;21,17,24,22;,
 4;24,17,16,26;,
 4;27,25,24,26;,
 4;16,18,27,26;,
 4;28,29,30,31;,
 4;28,31,5,4;,
 4;32,33,7,34;,
 4;32,34,30,29;,
 4;35,10,7,33;,
 4;36,14,13,37;,
 4;36,37,38,39;,
 4;36,39,18,14;,
 4;40,19,5,31;,
 4;40,31,30,41;,
 4;40,41,38,37;,
 4;40,37,13,19;,
 4;42,41,30,34;,
 4;42,34,7,23;,
 4;42,23,25,43;,
 4;42,43,38,41;,
 4;44,39,38,43;,
 4;44,43,25,27;,
 4;44,27,18,39;,
 4;45,46,47,48;,
 4;49,50,45,48;,
 4;51,52,49,48;,
 4;47,53,51,48;,
 4;2,54,55,3;,
 4;56,57,4,3;,
 4;55,58,56,3;,
 4;59,60,61,62;,
 4;63,64,59,62;,
 4;65,66,63,62;,
 4;61,67,65,62;,
 4;8,68,69,9;,
 4;69,54,2,9;,
 4;70,53,71,72;,
 4;73,74,70,72;,
 4;61,60,75,76;,
 4;77,67,61,76;,
 4;78,74,73,79;,
 4;75,60,78,79;,
 4;80,54,69,81;,
 4;70,74,82,83;,
 4;51,53,70,83;,
 4;84,52,51,83;,
 4;82,85,84,83;,
 4;78,60,59,86;,
 4;82,74,78,86;,
 4;87,85,82,86;,
 4;59,64,87,86;,
 4;88,58,55,89;,
 4;55,54,80,89;,
 4;47,46,90,91;,
 4;71,53,47,91;,
 4;92,93,94,11;,
 4;10,95,92,11;,
 4;94,68,8,11;,
 4;63,66,96,97;,
 4;98,64,63,97;,
 4;56,58,98,97;,
 4;96,57,56,97;,
 4;49,52,99,100;,
 4;101,50,49,100;,
 4;92,95,101,100;,
 4;99,93,92,100;,
 4;102,103,104,105;,
 4;104,106,107,105;,
 4;108,109,110,111;,
 4;112,113,108,111;,
 4;114,115,116,117;,
 4;110,109,114,117;,
 4;118,113,112,119;,
 4;107,106,118,119;,
 4;71,107,119,72;,
 4;119,112,73,72;,
 4;75,110,117,76;,
 4;117,116,77,76;,
 4;73,112,111,79;,
 4;111,110,75,79;,
 4;105,107,71,91;,
 4;90,102,105,91;,
 4;120,68,94,121;,
 4;69,68,120,81;,
 3;94,93,122;,
 3;121,94,122;,
 3;123,64,98;,
 3;99,52,124;,
 3;124,52,125;,
 3;52,84,125;,
 3;87,64,126;,
 3;64,123,126;,
 3;127,85,128;,
 3;87,126,129;,
 3;125,84,130;,
 4;131,132,127,128;,
 4;128,85,87,129;,
 4;84,85,127,130;,
 3;131,128,129;,
 3;127,132,130;,
 3;81,120,133;,
 3;80,81,134;,
 3;81,133,134;,
 3;88,89,135;,
 3;121,122,136;,
 4;133,136,130,132;,
 4;129,135,134,131;,
 4;131,134,133,132;,
 4;134,135,89,80;,
 4;121,136,133,120;,
 3;137,138,139;,
 3;140,141,142;,
 3;88,126,123;,
 3;124,125,122;,
 4;125,130,136,122;,
 4;88,135,129,126;,
 4;143,144,46,45;,
 4;143,45,50,145;,
 4;143,145,146,147;,
 4;143,147,148,144;,
 4;28,149,150,29;,
 4;28,4,57,151;,
 4;28,151,152,149;,
 4;153,154,155,156;,
 4;153,156,157,158;,
 4;153,158,66,65;,
 4;153,65,67,154;,
 4;32,159,160,33;,
 4;32,29,150,159;,
 4;161,162,148,163;,
 4;161,163,164,165;,
 4;166,167,155,154;,
 4;166,154,67,77;,
 4;168,165,164,169;,
 4;168,169,155,167;,
 4;170,159,150,171;,
 4;172,173,164,163;,
 4;172,163,148,147;,
 4;172,147,146,174;,
 4;172,174,175,173;,
 4;176,156,155,169;,
 4;176,169,164,173;,
 4;176,173,175,177;,
 4;176,177,157,156;,
 4;178,149,152,179;,
 4;178,171,150,149;,
 4;180,90,46,144;,
 4;180,144,148,162;,
 4;35,181,182,183;,
 4;35,183,95,10;,
 4;35,33,160,181;,
 4;184,96,66,158;,
 4;184,158,157,185;,
 4;184,185,152,151;,
 4;184,151,57,96;,
 4;186,187,146,145;,
 4;186,145,50,101;,
 4;186,101,95,183;,
 4;186,183,182,187;,
 4;188,189,103,102;,
 4;188,190,191,189;,
 4;192,193,194,195;,
 4;192,195,196,197;,
 4;198,116,115,199;,
 4;198,199,194,193;,
 4;200,197,196,201;,
 4;200,201,191,190;,
 4;161,200,190,162;,
 4;161,165,197,200;,
 4;166,198,193,167;,
 4;166,77,116,198;,
 4;168,192,197,165;,
 4;168,167,193,192;,
 4;180,162,190,188;,
 4;180,188,102,90;,
 4;202,181,160,203;,
 4;170,203,160,159;,
 3;204,182,181;,
 3;204,181,202;,
 3;185,157,205;,
 3;206,146,187;,
 3;207,146,206;,
 3;207,174,146;,
 3;208,157,177;,
 3;208,205,157;,
 3;209,175,210;,
 3;211,208,177;,
 3;212,174,207;,
 4;209,210,213,214;,
 4;211,177,175,209;,
 4;212,210,175,174;,
 3;211,209,214;,
 3;212,213,210;,
 3;215,203,170;,
 3;216,170,171;,
 3;216,215,170;,
 3;217,178,179;,
 3;218,204,202;,
 4;213,212,218,215;,
 4;214,216,217,211;,
 4;213,215,216,214;,
 4;171,178,217,216;,
 4;203,215,218,202;,
 3;219,220,221;,
 3;220,219,222;,
 3;205,208,179;,
 3;204,207,206;,
 4;204,218,212,207;,
 4;208,211,217,179;,
 4;223,224,225,226;,
 4;224,227,228,225;,
 4;227,229,230,228;,
 4;229,231,232,230;,
 4;231,233,234,232;,
 4;233,235,236,234;,
 4;235,237,238,236;,
 4;237,239,240,238;,
 4;239,241,242,240;,
 4;241,243,244,242;,
 4;243,245,246,244;,
 4;245,247,248,246;,
 4;247,249,250,248;,
 4;249,251,252,250;,
 4;251,253,254,252;,
 4;253,255,256,254;,
 3;257,224,223;,
 3;258,227,224;,
 3;259,229,227;,
 3;260,231,229;,
 3;261,233,231;,
 3;262,235,233;,
 3;263,237,235;,
 3;264,239,237;,
 3;265,241,239;,
 3;266,243,241;,
 3;267,245,243;,
 3;268,247,245;,
 3;269,249,247;,
 3;270,251,249;,
 3;271,253,251;,
 3;272,255,253;,
 3;124,122,93;,
 3;124,93,99;,
 3;182,204,206;,
 3;182,206,187;;
 
 MeshMaterialList {
  2;
  260;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.800000;0.674400;0.511200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.382400;0.708800;0.768800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  264;
  0.155706;0.083064;0.984305;,
  0.205941;0.674624;-0.708852;,
  0.238462;0.113966;-0.964442;,
  0.354285;0.873112;0.334900;,
  0.851495;0.351171;0.389404;,
  0.162220;0.241640;-0.956710;,
  0.861684;0.366295;-0.351181;,
  0.569245;0.816969;0.092315;,
  0.440935;-0.109514;-0.890833;,
  0.909023;0.040089;0.414814;,
  0.916021;0.151250;-0.371524;,
  0.379944;0.560431;-0.735907;,
  0.194842;0.332173;0.922875;,
  0.160572;0.612599;0.773912;,
  0.402202;0.710079;0.577946;,
  0.151921;0.936666;-0.315557;,
  0.514658;0.397847;-0.759503;,
  0.575169;0.288053;0.765641;,
  0.173573;0.951543;0.253846;,
  0.170938;0.121449;-0.977768;,
  0.114140;0.085355;0.989791;,
  0.239538;0.756777;0.608203;,
  0.557213;0.337733;0.758585;,
  0.292627;0.640473;-0.710045;,
  0.533010;0.321125;-0.782802;,
  0.149492;0.401491;-0.903580;,
  0.451761;0.878408;0.155921;,
  0.351338;0.906553;-0.233932;,
  0.933922;0.355434;0.038160;,
  0.208537;0.122205;-0.970349;,
  0.644275;0.138892;-0.752076;,
  0.167431;0.252900;0.952895;,
  0.992866;0.115704;-0.028809;,
  0.885017;0.272106;-0.377759;,
  0.872816;0.256062;0.415482;,
  0.537455;0.037442;0.842461;,
  0.537972;0.756771;-0.371326;,
  0.500338;-0.093449;-0.860772;,
  0.916981;-0.196742;0.347044;,
  0.909991;-0.152410;-0.385600;,
  0.303726;0.670707;0.676685;,
  0.125246;0.322330;0.938305;,
  0.371263;0.549893;-0.748186;,
  0.185307;0.981042;-0.056725;,
  0.415105;0.680690;-0.603614;,
  0.454399;0.636094;0.623623;,
  0.666018;0.486622;-0.565348;,
  0.219800;0.065869;-0.973319;,
  0.243550;0.071239;-0.967269;,
  0.194868;0.080458;0.977524;,
  0.135758;0.000961;0.990742;,
  0.501865;0.590368;0.632137;,
  0.205041;0.301848;-0.931045;,
  0.386107;0.810810;0.439895;,
  0.413519;0.849738;-0.327028;,
  0.540822;0.255418;0.801420;,
  0.584171;0.211959;-0.783465;,
  0.963545;0.266749;0.020648;,
  0.639582;-0.090403;-0.763388;,
  0.525442;-0.161311;0.835398;,
  0.985850;-0.141320;-0.090157;,
  0.208602;0.357852;0.910180;,
  0.631439;0.764286;-0.130968;,
  0.526283;0.820072;-0.224738;,
  -0.023112;-0.999704;0.007612;,
  0.017236;-0.990930;0.133269;,
  -0.159004;-0.987089;-0.019304;,
  -0.085640;-0.980867;0.174831;,
  -0.058745;-0.990438;0.124824;,
  -0.067526;-0.992941;0.097512;,
  -0.116701;-0.990405;-0.074019;,
  0.000000;0.578606;-0.815607;,
  0.000000;0.223605;-0.974680;,
  0.000000;0.105736;-0.994394;,
  0.000000;0.097789;0.995207;,
  -0.000000;0.348201;0.937420;,
  0.000000;0.554835;0.831961;,
  0.000000;0.958581;0.284820;,
  0.000000;0.942531;-0.334119;,
  0.000000;0.298544;-0.954396;,
  0.000000;0.142374;-0.989813;,
  0.000000;0.085931;0.996301;,
  0.000000;0.157061;0.987589;,
  0.000000;0.542419;0.840108;,
  0.000000;0.414420;-0.910086;,
  -0.000000;0.092047;-0.995755;,
  0.000000;0.260211;0.965552;,
  0.000000;0.276028;0.961149;,
  -0.000000;0.432805;-0.901487;,
  0.000000;0.556668;0.830735;,
  0.000000;0.997804;-0.066232;,
  0.000000;0.626285;-0.779594;,
  -0.000000;0.091292;-0.995824;,
  0.000000;0.023060;0.999734;,
  0.000000;-0.992865;0.119242;,
  0.000000;-0.983971;0.178330;,
  0.487552;0.791586;0.368354;,
  0.285433;0.490272;0.823505;,
  0.498710;-0.060203;0.864675;,
  0.839690;-0.314692;0.442594;,
  0.928075;-0.370107;0.041206;,
  0.901526;-0.400935;-0.162794;,
  0.785610;-0.342432;-0.515323;,
  0.964412;-0.264281;0.008083;,
  0.944621;-0.273385;-0.181526;,
  0.857646;-0.370544;-0.356568;,
  0.935011;-0.310974;0.170437;,
  0.909250;-0.406745;0.088446;,
  0.878942;-0.464846;-0.106675;,
  0.787983;-0.471787;-0.395600;,
  0.906154;-0.372336;0.200627;,
  -0.155706;0.083064;0.984305;,
  -0.205941;0.674624;-0.708852;,
  -0.238462;0.113966;-0.964442;,
  -0.354285;0.873112;0.334900;,
  -0.851495;0.351171;0.389404;,
  -0.162220;0.241640;-0.956710;,
  -0.861684;0.366295;-0.351181;,
  -0.569245;0.816969;0.092315;,
  -0.440935;-0.109514;-0.890833;,
  -0.909023;0.040089;0.414814;,
  -0.916021;0.151250;-0.371524;,
  -0.379944;0.560431;-0.735907;,
  -0.194842;0.332173;0.922875;,
  -0.160572;0.612599;0.773912;,
  -0.402202;0.710079;0.577946;,
  -0.151921;0.936666;-0.315557;,
  -0.514658;0.397847;-0.759503;,
  -0.575169;0.288053;0.765641;,
  -0.173573;0.951543;0.253846;,
  -0.170938;0.121449;-0.977768;,
  -0.114140;0.085355;0.989791;,
  -0.239538;0.756777;0.608203;,
  -0.557213;0.337733;0.758585;,
  -0.292627;0.640473;-0.710045;,
  -0.533010;0.321125;-0.782802;,
  -0.149492;0.401491;-0.903580;,
  -0.451761;0.878408;0.155921;,
  -0.351338;0.906553;-0.233932;,
  -0.933922;0.355434;0.038160;,
  -0.208537;0.122205;-0.970349;,
  -0.644275;0.138892;-0.752076;,
  -0.167431;0.252900;0.952895;,
  -0.992866;0.115704;-0.028809;,
  -0.885017;0.272106;-0.377759;,
  -0.872816;0.256062;0.415482;,
  -0.537455;0.037442;0.842461;,
  -0.537972;0.756771;-0.371326;,
  -0.500338;-0.093449;-0.860772;,
  -0.916981;-0.196742;0.347044;,
  -0.909991;-0.152410;-0.385600;,
  -0.303726;0.670707;0.676685;,
  -0.125246;0.322330;0.938305;,
  -0.371263;0.549893;-0.748186;,
  -0.185307;0.981042;-0.056725;,
  -0.415105;0.680690;-0.603614;,
  -0.454399;0.636094;0.623623;,
  -0.666018;0.486622;-0.565348;,
  -0.219800;0.065869;-0.973319;,
  -0.243550;0.071239;-0.967269;,
  -0.194868;0.080458;0.977524;,
  -0.135758;0.000961;0.990742;,
  -0.501865;0.590368;0.632137;,
  -0.205041;0.301848;-0.931045;,
  -0.386107;0.810810;0.439895;,
  -0.413519;0.849738;-0.327028;,
  -0.540822;0.255418;0.801420;,
  -0.584171;0.211959;-0.783465;,
  -0.963545;0.266749;0.020648;,
  -0.639582;-0.090403;-0.763388;,
  -0.525442;-0.161311;0.835398;,
  -0.985850;-0.141320;-0.090157;,
  -0.208602;0.357852;0.910180;,
  -0.631439;0.764286;-0.130968;,
  -0.526283;0.820072;-0.224738;,
  0.023112;-0.999704;0.007612;,
  -0.017236;-0.990930;0.133269;,
  0.159004;-0.987089;-0.019304;,
  0.085640;-0.980867;0.174831;,
  0.058745;-0.990438;0.124824;,
  0.067526;-0.992941;0.097512;,
  0.116701;-0.990405;-0.074019;,
  -0.487552;0.791586;0.368354;,
  -0.285433;0.490272;0.823505;,
  -0.498710;-0.060203;0.864675;,
  -0.839690;-0.314692;0.442594;,
  -0.928075;-0.370107;0.041206;,
  -0.901526;-0.400935;-0.162794;,
  -0.785610;-0.342432;-0.515323;,
  -0.964412;-0.264281;0.008083;,
  -0.944621;-0.273385;-0.181526;,
  -0.857646;-0.370544;-0.356568;,
  -0.935011;-0.310974;0.170437;,
  -0.909250;-0.406745;0.088446;,
  -0.878942;-0.464846;-0.106675;,
  -0.787983;-0.471787;-0.395600;,
  -0.906154;-0.372336;0.200627;,
  0.000000;-0.972122;0.234476;,
  0.011855;-0.976417;0.215569;,
  0.084961;-0.987682;0.131401;,
  0.171408;-0.985164;0.008460;,
  0.184358;-0.980765;-0.064135;,
  0.140832;-0.987398;-0.072193;,
  0.130001;-0.991193;-0.025206;,
  0.093431;-0.995452;0.018593;,
  0.000000;-0.999725;0.023443;,
  -0.093431;-0.995452;0.018593;,
  -0.130002;-0.991193;-0.025206;,
  -0.140832;-0.987398;-0.072193;,
  -0.184358;-0.980765;-0.064135;,
  -0.171408;-0.985164;0.008460;,
  -0.084961;-0.987682;0.131401;,
  -0.011855;-0.976417;0.215569;,
  0.000000;-0.962354;0.271800;,
  0.045804;-0.969953;0.238940;,
  0.097989;-0.983517;0.151959;,
  0.153337;-0.986594;0.055856;,
  0.192552;-0.980915;-0.027025;,
  0.189729;-0.975285;-0.113232;,
  0.145809;-0.976820;-0.156722;,
  0.074750;-0.984345;-0.159619;,
  0.000000;-0.986493;-0.163801;,
  -0.074750;-0.984345;-0.159619;,
  -0.145809;-0.976820;-0.156722;,
  -0.189729;-0.975285;-0.113232;,
  -0.192552;-0.980915;-0.027025;,
  -0.153337;-0.986594;0.055856;,
  -0.097989;-0.983517;0.151959;,
  -0.045804;-0.969953;0.238940;,
  0.000000;-1.000000;-0.000000;,
  0.758354;0.397146;0.516889;,
  0.775231;0.346215;0.528348;,
  -0.758354;0.397146;0.516889;,
  -0.775231;0.346215;0.528348;,
  0.564746;0.321613;0.760018;,
  0.840729;0.375075;0.390504;,
  0.907820;0.416924;0.045139;,
  0.496399;0.434618;-0.751462;,
  0.135772;0.368553;-0.919638;,
  0.000000;0.361362;-0.932425;,
  0.830482;0.454543;-0.322009;,
  0.213996;0.326946;0.920496;,
  0.000000;0.359694;0.933070;,
  0.905713;-0.419210;0.062818;,
  0.913534;-0.374690;0.158313;,
  0.876021;-0.460398;-0.143602;,
  0.712432;-0.440187;-0.546513;,
  0.777200;-0.459284;-0.430137;,
  0.907947;-0.357370;0.218903;,
  0.879477;-0.345856;0.326960;,
  -0.840729;0.375075;0.390504;,
  -0.564746;0.321613;0.760018;,
  -0.907820;0.416924;0.045139;,
  -0.135772;0.368553;-0.919638;,
  -0.496399;0.434618;-0.751462;,
  -0.830482;0.454543;-0.322009;,
  -0.213996;0.326946;0.920496;,
  -0.913534;-0.374690;0.158313;,
  -0.905713;-0.419210;0.062818;,
  -0.876021;-0.460398;-0.143602;,
  -0.777200;-0.459284;-0.430137;,
  -0.712432;-0.440187;-0.546513;,
  -0.879477;-0.345856;0.326960;,
  -0.907947;-0.357370;0.218903;;
  260;
  4;42,62,27,1;,
  4;71,88,42,1;,
  4;51,83,21,3;,
  4;27,62,51,3;,
  4;21,83,76,13;,
  4;44,91,78,15;,
  4;43,63,44,15;,
  4;78,90,43,15;,
  4;42,88,79,16;,
  4;46,62,42,16;,
  4;44,63,46,16;,
  4;79,91,44,16;,
  4;51,62,230,17;,
  4;82,83,51,17;,
  4;45,89,82,17;,
  4;230,231,45,17;,
  4;45,63,43,18;,
  4;77,89,45,18;,
  4;43,90,77,18;,
  4;112,138,173,153;,
  4;112,153,88,71;,
  4;114,132,83,162;,
  4;114,162,173,138;,
  4;124,76,83,132;,
  4;126,78,91,155;,
  4;126,155,174,154;,
  4;126,154,90,78;,
  4;127,79,88,153;,
  4;127,153,173,157;,
  4;127,157,174,155;,
  4;127,155,91,79;,
  4;128,232,173,162;,
  4;128,162,83,82;,
  4;128,82,89,156;,
  4;128,156,233,232;,
  4;129,154,174,156;,
  4;129,156,89,77;,
  4;129,77,90,154;,
  4;74,86,31,0;,
  4;50,93,74,0;,
  4;35,59,50,0;,
  4;31,55,35,0;,
  4;27,54,23,1;,
  4;25,84,71,1;,
  4;23,52,25,1;,
  4;30,56,29,2;,
  4;47,58,30,2;,
  4;73,92,47,2;,
  4;29,85,73,2;,
  4;21,53,26,3;,
  4;26,54,27,3;,
  4;34,55,22,4;,
  4;28,57,34,4;,
  4;29,56,24,5;,
  4;72,85,29,5;,
  4;33,57,28,6;,
  4;24,56,33,6;,
  4;36,54,26,7;,
  4;34,57,32,9;,
  4;35,55,34,9;,
  4;38,59,35,9;,
  4;32,60,38,9;,
  4;33,56,30,10;,
  4;32,57,33,10;,
  4;39,60,32,10;,
  4;30,58,39,10;,
  4;37,52,23,11;,
  4;23,54,36,11;,
  4;31,86,75,12;,
  4;22,55,31,12;,
  4;41,61,40,13;,
  4;76,87,41,13;,
  4;40,53,21,13;,
  4;47,92,80,19;,
  4;48,58,47,19;,
  4;25,52,48,19;,
  4;80,84,25,19;,
  4;50,59,49,20;,
  4;81,93,50,20;,
  4;41,87,81,20;,
  4;49,61,41,20;,
  4;95,205,206,67;,
  4;206,207,68,67;,
  4;210,211,69,66;,
  4;70,209,210,66;,
  4;212,197,94,65;,
  4;69,211,212,65;,
  4;208,209,70,64;,
  4;68,207,208,64;,
  4;22,234,235,4;,
  4;235,236,28,4;,
  4;24,237,238,5;,
  4;238,239,72,5;,
  4;28,236,240,6;,
  4;240,237,24,6;,
  4;241,234,22,12;,
  4;75,242,241,12;,
  4;96,53,40,14;,
  4;26,53,96,7;,
  3;40,61,97;,
  3;14,40,97;,
  3;8,58,48;,
  3;49,59,98;,
  3;98,59,99;,
  3;59,38,99;,
  3;39,58,102;,
  3;58,8,102;,
  3;103,60,104;,
  3;39,102,105;,
  3;99,38,106;,
  4;101,100,103,104;,
  4;104,60,39,105;,
  4;38,60,103,106;,
  3;101,104,105;,
  3;103,100,106;,
  3;243,244,107;,
  3;245,243,108;,
  3;243,107,108;,
  3;246,247,109;,
  3;248,249,110;,
  4;107,110,106,100;,
  4;105,109,108,101;,
  4;101,108,107,100;,
  4;108,109,247,245;,
  4;248,110,107,244;,
  3;37,8,52;,
  3;48,52,8;,
  3;37,102,8;,
  3;98,99,249;,
  4;99,106,110,249;,
  4;37,109,105,102;,
  4;111,142,86,74;,
  4;111,74,93,161;,
  4;111,161,170,146;,
  4;111,146,166,142;,
  4;112,134,165,138;,
  4;112,71,84,136;,
  4;112,136,163,134;,
  4;113,140,167,141;,
  4;113,141,169,158;,
  4;113,158,92,73;,
  4;113,73,85,140;,
  4;114,137,164,132;,
  4;114,138,165,137;,
  4;115,133,166,145;,
  4;115,145,168,139;,
  4;116,135,167,140;,
  4;116,140,85,72;,
  4;117,139,168,144;,
  4;117,144,167,135;,
  4;118,137,165,147;,
  4;120,143,168,145;,
  4;120,145,166,146;,
  4;120,146,170,149;,
  4;120,149,171,143;,
  4;121,141,167,144;,
  4;121,144,168,143;,
  4;121,143,171,150;,
  4;121,150,169,141;,
  4;122,134,163,148;,
  4;122,147,165,134;,
  4;123,75,86,142;,
  4;123,142,166,133;,
  4;124,151,172,152;,
  4;124,152,87,76;,
  4;124,132,164,151;,
  4;130,80,92,158;,
  4;130,158,169,159;,
  4;130,159,163,136;,
  4;130,136,84,80;,
  4;131,160,170,161;,
  4;131,161,93,81;,
  4;131,81,87,152;,
  4;131,152,172,160;,
  4;178,204,205,95;,
  4;178,179,203,204;,
  4;177,180,199,200;,
  4;177,200,201,181;,
  4;176,94,197,198;,
  4;176,198,199,180;,
  4;175,181,201,202;,
  4;175,202,203,179;,
  4;115,250,251,133;,
  4;115,139,252,250;,
  4;116,253,254,135;,
  4;116,72,239,253;,
  4;117,255,252,139;,
  4;117,135,254,255;,
  4;123,133,251,256;,
  4;123,256,242,75;,
  4;125,151,164,182;,
  4;118,182,164,137;,
  3;183,172,151;,
  3;183,151,125;,
  3;159,169,119;,
  3;184,170,160;,
  3;185,170,184;,
  3;185,149,170;,
  3;188,169,150;,
  3;188,119,169;,
  3;190,171,189;,
  3;191,188,150;,
  3;192,149,185;,
  4;190,189,186,187;,
  4;191,150,171,190;,
  4;192,189,171,149;,
  3;191,190,187;,
  3;192,186,189;,
  3;193,257,258;,
  3;194,258,259;,
  3;194,193,258;,
  3;195,260,261;,
  3;196,262,263;,
  4;186,192,196,193;,
  4;187,194,195,191;,
  4;186,193,194,187;,
  4;259,260,195,194;,
  4;257,193,196,263;,
  3;163,119,148;,
  3;119,163,159;,
  3;119,188,148;,
  3;262,185,184;,
  4;262,196,192,185;,
  4;188,191,195,148;,
  4;213,214,198,197;,
  4;214,215,199,198;,
  4;215,216,200,199;,
  4;216,217,201,200;,
  4;217,218,202,201;,
  4;218,219,203,202;,
  4;219,220,204,203;,
  4;220,221,205,204;,
  4;221,222,206,205;,
  4;222,223,207,206;,
  4;223,224,208,207;,
  4;224,225,209,208;,
  4;225,226,210,209;,
  4;226,227,211,210;,
  4;227,228,212,211;,
  4;228,213,197,212;,
  3;229,214,213;,
  3;229,215,214;,
  3;229,216,215;,
  3;229,217,216;,
  3;229,218,217;,
  3;229,219,218;,
  3;229,220,219;,
  3;229,221,220;,
  3;229,222,221;,
  3;229,223,222;,
  3;229,224,223;,
  3;229,225,224;,
  3;229,226,225;,
  3;229,227,226;,
  3;229,228,227;,
  3;229,213,228;,
  3;98,97,61;,
  3;98,61,49;,
  3;172,183,184;,
  3;172,184,160;;
 }
 MeshTextureCoords {
  273;
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  1.000000;0.000000;,
  1.000000;0.000000;,
  0.000000;0.750000;,
  0.062500;0.750000;,
  0.062500;0.500000;,
  0.000000;0.500000;,
  0.125000;0.750000;,
  0.125000;0.500000;,
  0.187500;0.750000;,
  0.187500;0.500000;,
  0.250000;0.750000;,
  0.250000;0.500000;,
  0.312500;0.750000;,
  0.312500;0.500000;,
  0.375000;0.750000;,
  0.375000;0.500000;,
  0.437500;0.750000;,
  0.437500;0.500000;,
  0.500000;0.750000;,
  0.500000;0.500000;,
  0.562500;0.750000;,
  0.562500;0.500000;,
  0.625000;0.750000;,
  0.625000;0.500000;,
  0.687500;0.750000;,
  0.687500;0.500000;,
  0.750000;0.750000;,
  0.750000;0.500000;,
  0.812500;0.750000;,
  0.812500;0.500000;,
  0.875000;0.750000;,
  0.875000;0.500000;,
  0.937500;0.750000;,
  0.937500;0.500000;,
  1.000000;0.750000;,
  1.000000;0.500000;,
  0.031250;1.000000;,
  0.093750;1.000000;,
  0.156250;1.000000;,
  0.218750;1.000000;,
  0.281250;1.000000;,
  0.343750;1.000000;,
  0.406250;1.000000;,
  0.468750;1.000000;,
  0.531250;1.000000;,
  0.593750;1.000000;,
  0.656250;1.000000;,
  0.718750;1.000000;,
  0.781250;1.000000;,
  0.843750;1.000000;,
  0.906250;1.000000;,
  0.968750;1.000000;;
 }
}
