
a = 1:25

a = a'

a(:,2) = [
 63 ,
 32 ,
 37 ,
 67 ,
 93 ,
 68 ,
 64 ,
 66 ,
 72 ,
 73 ,
 84 ,
 75 ,
 97 ,
 91 ,
 78 ,
 91 ,
 80 ,
 56 ,
 74 ,
 63 ,
 46 ,
 66 ,
 63 ,
 95 ,
 58
] ;


a(:,3) = [
0.8010 ,
0.0673 ,
0.1235 ,
0.2488 ,
0.9314 ,
0.5443 ,
4.6128 ,
0.9033 ,
0.4688 ,
0.5379 ,
1.5151 ,
3.2720 ,
1.9190 ,
2.0561 ,
1.3183 ,
1.9640 ,
2.0648 ,
3.9024 ,
4.0438 ,
0.3889 ,
1.6373 ,
1.0254 ,
1.8974 ,
3.3067 ,
5.4602
]


a(:,4) = [
2.3242,
0.4029,
0.4697,
1.8703,
0.2762,
3.7109,
0.9137,
1.7610,
1.0826,
1.2822,
1.9611,
1.5947,
1.1976,
1.7748,
2.9317,
0.2240,
1.4460,
1.6684,
1.3792,
2.4719,
0.9565,
0.8127,
1.2088,
1.5144,
1.3776
] ;

b(:,1) = 1:27 ;

b(:,2) = [
0.4776,
0.2555,
0.3230,
0.3166,
0.3383,
0.2588,
0.2606,
0.2965,
0.2566,
0.2707,
0.3181,
0.2558,
0.2623,
0.2568,
0.2561,
0.2701,
0.2605,
0.2553,
0.2559,
0.2554,
0.2553,
0.3199,
0.2554,
0.2554,
0.3194,
0.2561,
0.2554
]


#a(:,1) es indices
#a(:,2) es generaciones
#a(:,3) fitness
#a(:,4) errores
#a(:,5) fitness parameters

plot(a(:,1) , a(:,2))
axis([1,25,0,100])
xlabel "Instancia"
ylabel "Generacion"
pause

plot(a(:,1) , a(:,3))
xlabel "Instancia"
ylabel "Fitness"
pause
plot(a(:,1) , a(:,4))
xlabel "Instancia"
ylabel "Error"
pause







