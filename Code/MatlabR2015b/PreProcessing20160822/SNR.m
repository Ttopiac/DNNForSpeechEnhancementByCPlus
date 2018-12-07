function ret = SNR( mother, child )
    ret = 20*log10( RMS(mother)/RMSE(mother, child) );
end
function ret = RMS( data )
    ret = sqrt( sum(sum(data.^2))/(size(data,1)*size(data,2)) ); 
end
function ret = RMSE( mother, child )
    Diff =  mother - child;
    ret = RMS( Diff ); 
end

