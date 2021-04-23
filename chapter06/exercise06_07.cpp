// write a grammar for bitwise logical expressions

/*

Expression :
    Quanternary
    Expression "|" Quanternary

Quanternary :
    Tertiary
    Quanternary "^" Tertiary

Tertiary :
    Secondary
    Tertiary "&" Secondary

Secondary :
    Primary
    "!" Primary
    "~" Primary

Primary :
    Number
    "(" Expression ")"
    
Number :
    floating-point-literal

*/