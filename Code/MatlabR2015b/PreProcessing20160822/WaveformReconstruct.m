function [ T ] = WaveformReconstruct( magF, phaF)
% 程式功能：ExtractFeature程式扣除第一步驟後的Inverse Function。
%% 
    magF = power( 10, magF);
    magF = magF-1;
    frameF = complex(magF.*cos(phaF), magF.*sin(phaF));
%%
    T = GetTfromFramingF( frameF );
end

function T = GetTfromFramingF( frameF )
% 程式功能：將被切完音框的頻域資料ifft後重組音框原始時域陣列
% 輸入參數說明：
%   T               → 要FFT之陣列檔案
%   frameSize       → 音框大小
% 輸出參數說明：
%   frameF          → 切完音框後之頻域陣列
%%
    frameSize = size( frameF, 1);
    frames = size( frameF, 2);
    frameT = frameF*0;
    for i = 1:frames
        frameT( :, i) = ifft( frameF( :, i), frameSize);  
    end
    T = zeros( frameSize*frames, 1);
    for i = 1:frames
        T(frameSize*(i-1)+1:frameSize*i, 1) = frameT(:, i);
    end
end

function T = GetTfromFramingF( frameF )
% 程式功能：將被切完音框的頻域資料ifft後重組音框原始時域陣列
% 輸入參數說明：
%   T               → 要FFT之陣列檔案
%   frameSize       → 音框大小
% 輸出參數說明：
%   frameF          → 切完音框後之頻域陣列
%%
    frameSize = size( frameF, 1);
    frames = size( frameF, 2);
    frameT = frameF*0;
    for i = 1:frames
        frameT( :, i) = ifft( frameF( :, i), frameSize);  
    end
    T = zeros( frameSize*frames, 1);
    for i = 1:frames
        T(frameSize*(i-1)+1:frameSize*i, 1) = frameT(:, i);
    end
end

