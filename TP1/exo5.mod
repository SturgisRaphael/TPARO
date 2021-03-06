var M1 >= 2000;
var M2 >= 1750;
var M3 >= 2000;
var M4 >= 2750;
var M5 >= 2000;
var M6 >= 1750;
var S1 <= 6000;
var S2 <= 6000;
var S3 <= 6000;
var S4 <= 6000;
var S5 <= 6000;
var S6 <= 6000;
minimize obj: 240*M1 + 3.6*S1 + 250*M2 + 3.75*S2 + 265*M3 + 3.975*S3 + 285*M4 + 4.275*S4 + 280*M5 + 4.2*S5 + 285*M6 + 4.275*S6;
s.t. c1: 2750 + M1 - 1000 = S1;
s.t. c2: S1 + M2 - 4500 = S2;
s.t. c3: S2 + M3 - 6000 = S3;
s.t. c4: S3 + M4 - 5500 = S4;
s.t. c5: S4 + M5 - 3500 = S5;
s.t. c6: S5 + M6 - 4000 = S6;
s.t. c7: 4000 >= M1;
s.t. c8: 3500 >= M2;
s.t. c9: 4000 >= M3;
s.t. c10: 4500 >= M4;
s.t. c11: 4000 >= M5;
s.t. c12: 3500 >= M6;
s.t. c13: 1500 <= S1;
s.t. c14: 1500 <= S2;
s.t. c15: 1500 <= S3;
s.t. c16: 1500 <= S4;
s.t. c17: 1500 <= S5;
s.t. c18: 1500 <= S6;
solve;
display M1, M2 ,M3 ,M4 ,M5, M6;
end; 
