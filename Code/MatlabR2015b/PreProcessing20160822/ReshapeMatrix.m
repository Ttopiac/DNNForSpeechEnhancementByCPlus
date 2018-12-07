function [reshapeM] = ReshapeMatrix( input, ratio)
    if ratio > 1
        reshapeM = reshape( input( :, 1:size(input,2)-mod( size(input,2), ratio) ), floor(size(input,1)*ratio), floor(size(input,2)/ratio));
    elseif ratio < 1 && ratio > 0
        reshapeM = reshape( input( 1:size(input,1)-mod( size(input,1), 1/ratio), :), floor(size(input,1)*ratio), floor(size(input,2)/ratio));
    elseif ratio == 1
        reshapeM = input;
    else 
        fprintf('Warning: ratio need to bigger than 0\n');
        reshapeM = 'Warning';
    end
end
