
a = [ 
 129.3718385604594232  , 
 58.6751736220494990  , 
 30.0485959566651815  , 
 16.6455007129337780  , 
 8.3622299966159801  , 
 6.4348608116252972  , 
 6.4348608116252972  , 
 6.4348608116252972  , 
 5.0445203693052250  , 
 7.8291457716051323  , 
 7.8291457716051323  , 
 6.8243798122599495  , 
 6.8243798122599495  , 
 6.8243798122599495  , 
 6.8243798122599495  , 
 6.6243206161041108  , 
 6.8243798122599495  , 
 6.8243798122599495  , 
 6.5104688064166272  , 
 6.8243798122599495  , 
 5.0170483538405541  , 
 5.0170483538405541  , 
 4.4767080971486033  , 
 5.0170483538405541  , 
 5.0170483538405541  , 
 5.0170483538405541  , 
 5.0170483538405541  , 
 5.0170483538405541  , 
 4.0187049478238652  , 
 3.2895008459493753  , 
 3.2895008459493753  , 
 2.8857735141267380  , 
 2.8857735141267380  , 
 3.2895008459493753  , 
 3.2895008459493753  , 
 3.2895008459493753  , 
 3.2895008459493753  , 
 3.2895008459493753  , 
 2.4258628450297861  , 
 2.4258628450297861  , 
 2.4258628450297861  , 
 2.4258628450297861  , 
 2.4258628450297861  , 
 0.8251958927627759  , 
 0.8251958927627759  , 
 0.8251958927627759  , 
 0.8251958927627759  , 
 0.7912809002275357  , 
 0.8251958927627759  , 
 0.8251958927627759  , 
 0.8251958927627759  , 
 0.8251958927627759  , 
 0.4803200534115786  , 
 0.4792909415141921  , 
 0.3667074121514650  , 
 0.3195650362226474  , 
 0.3195650362226474  , 
 0.3202996202955578  , 
 0.3202996202955578  , 
 0.3202996202955578  , 
 0.3200479515499924  , 
 0.3200479515499924  , 
 0.3200479515499924  , 
 0.3200479515499924  , 
 0.3200479515499924  , 
 0.3198942648286638  , 
 0.3200479515499924  , 
 0.3200479515499924  , 
 0.3200479515499924  , 
 0.3200479515499924  , 
 0.3181801791784207  , 
 0.3181801791784207  , 
 0.3180684350799392  , 
 0.3180684350799392  , 
 0.3180715536565417  , 
 0.3180715536565417  , 
 0.3180663830643911  , 
 0.3180666726251768  , 
 0.3180607561733003  , 
 0.3180607561733003  , 
 0.3180607561733003  , 
 0.3180607561733003  , 
 0.3180607561733003  , 
 0.3180607561733003  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3180625314126381  , 
 0.3179903033204970  , 
 0.3179257258134959  , 
 0.3179257613483840  , 
 0.3179256549556210 
 ] ;
 

for i=1:size(a)
    a(i) = log(a(i)) ;
end 


plot( 0:size(a)(1)-1 , a )
xlabel "Generacion"
ylabel "log(Best Fitness)"
pause
