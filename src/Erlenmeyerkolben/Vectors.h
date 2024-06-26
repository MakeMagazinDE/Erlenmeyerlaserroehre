//////////////////////////////////////////////////////////////////////////////
// Vektorkoordinaten für den MAKE-Schriftzug und die NCC-1701 Enterprise
// Die Daten werden im Programmspeicher abgelegt, 
// um Variablenspeicher zu sparen
//
// veröffentlicht in der MAKE Ausgabe 3/2024
//
// Ulrich Schmerold
// 4/2024
//////////////////////////////////////////////////////////////////////////////


#ifndef VECTORS_H
#define VECTORS_H

// -------------------------    Vektordaten für den Make-Schriftzug
const int points_MAKE = 121;
const byte px_MAKE[122] ={ 20, 20, 34, 42, 51, 64, 64, 56, 56, 47, 38, 29, 29, 20, 73, 74, 76, 79, 82, 85, 90, 94, 97, 99,100,100,101,102, 93, 92, 90, 88, 86, 82, 78, 74, 72, 71, 71, 73, 76, 80, 85, 91, 91, 90, 87, 83, 81, 80, 72, 91, 91, 90, 87, 83, 80, 80, 82, 86, 91,108,108,117,117,121,129,139,127,138,127,117,117,106,151,163,163,160,157,153,151,150,150,172,172,170,168,163,159,154,148,144,142,141,141,143,146,150,155,161,166,169,171,163,162,159,155,152,151,150,181,189,189,181,181,181,189,189,181,181, 20, 20};
const byte py_MAKE[122] ={189,143,143,174,143,143,189,189,153,189,189,153,189,189,165,160,158,156,155,155,155,156,158,160,163,182,186,189,189,185,187,188,189,189,189,187,184,181,177,173,171,170,169,167,165,163,162,162,164,166,165,173,178,181,183,183,181,178,175,174,173,143,189,189,178,174,189,189,168,156,156,167,143,143,169,169,166,163,162,163,165,169,174,174,169,164,160,156,155,155,157,161,166,171,176,181,185,188,189,189,187,184,180,178,181,183,183,181,178,174,156,156,164,164,155,180,180,189,189,179,143,189};
const byte pc_MAKE[122] ={  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  0,  1,  1,  1,  1,  0,  0};

// -------------------------  Vektordaten für die NCC-1701 Enterprise
const int points_NCC = 132;
const byte px_NCC[133]  ={ 60, 44, 32, 11, 10, 11, 14, 19, 46, 41, 35, 32, 31, 35, 41, 42, 49, 59, 76, 92,104,116,111,116,118,125,131,134,151,155,155,151,136,131,130,115,111,106,118,104, 94, 87, 83, 82, 85, 92,101,110,117,124,128,129,125,119,111,102, 92, 87, 81, 72, 68, 67, 75, 88,155,164,186,201,213,225,235,241,247,245,237,216,192,159,114, 80, 58, 47, 39, 48, 49, 55, 71, 95,121,150,177,198,217,232,238,241,178,173,160, 50, 47, 41, 36, 34, 33, 37, 41, 44, 80, 78, 41, 39, 74, 78,123,117,112,109,109,111,115,121,127,121,113,107,105,105,108,114,119,125, 60};
const byte py_NCC[133]  ={ 34, 36, 39, 65, 70, 74, 76, 76, 57, 57, 54, 49, 40, 34, 34, 39, 52, 58, 63, 66, 68, 63, 61, 62, 65, 70, 71, 69, 69, 70, 75, 76, 76, 75, 71, 87, 96, 96, 65, 68, 98,104,110,120,130,135,138,138,136,130,121,112,105, 98, 96, 96, 99,103,104,108,111,121,127,132, 70, 69, 67, 65, 62, 59, 54, 48, 36, 30, 25, 18, 14, 12, 12, 17, 23, 28, 36, 50, 46, 41, 35, 31, 28, 28, 29, 31, 35, 40, 43, 48, 60, 61, 70, 53, 56, 55, 52, 48, 40, 34, 34, 58,106,109, 60, 62,109,109,103,103,107,112,118,124,127,128,125,100,101,105,111,121,128,131,131,130, 34};
const byte pc_NCC[133]  ={  0,  0,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0,  1,  1,  1,  1,  1,  1,  1,  1,  0};


// --------------------------  Testbild
const int points_Testbild = 38;
const byte px_Testbild[39]  ={125,109, 94,177,225,200,175,113,152,200,188,165,175,113,118,165,122,106, 61, 31, 36, 84, 30, 60, 85,106,116, 85,115,118, 94, 99,112,133,134,133,209,226,125};
const byte py_Testbild[39]  ={ 59, 58, 57, 39, 79, 87,118, 94, 71, 87,153,199,117, 95,170,200,173,199,205,173,132, 95,174,205, 95,199,141, 95,120, 90, 57,106,187,238,182,238,189, 78, 59};
const byte pc_Testbild[39]  ={  0,  0,  0,  1,  1,  1,  4,  4,  4,  4,  4,  4,  4,  0,  4,  4,  0,  2,  2,  2,  2,  2,  2,  0,  2,  2,  0,  2,  2,  0,  1,  1,  0,  1,  1,  0,  1,  1,  0};

#endif
