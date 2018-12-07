function [magF, phaF, FS] = ExtractFeature( fileName, frameSize)
% 程式功能：將clean sample的Matrix之資料經過以下步驟處理
%           第一步驟：讀取wav檔案輸出時域資料以及sample rate
%           後續步驟：   將時域資料切成數個音框大小為frameSize的音框    
%                        將每個音框做傅立葉轉換為頻域資料
%                        將頻域資料(為complex number)轉換為magnitude以及phase
%                        將magnitude資料加 1 後取log
% 輸入參數說明：
%   fileName        → 要讀取之wav檔名以及要寫入的txt檔名 (不包括副檔名)
%   frameSize       → 音框大小
% 輸出參數說明：
%   norF            → 經過上述步驟處理過後之音訊陣列
%   phaF            → 經過fft步驟處理過後之phase陣列
%   FS              → sampling rate(取樣頻率)
%%
    [ T, FS] = audioread( fileName);
%%
    [ frameF] = FramingFFTfromWav( T, frameSize);
%%
    [ phaF, magF] = ExtractMagAndPhase( frameF);
    magF = magF+1;
    magF = log10(magF);
end

function [ phaF, magF] = ExtractMagAndPhase( frameF)
% 程式功能：將complex variables取其phase及magnitude後輸出
% 輸入參數說明：
%   frameF          → 內涵complex variables的陣列
% 輸出參數說明：
%   phaF          → phase
%   magF          → magnitude
    %%
    frames = size(frameF,2);
    phaF = frameF*0;
    for i = 1:frames
      phaF( :, i) = phase(frameF(:,i));  
    end
    %%
	magF = abs(frameF);
end

function [ frameF] = FramingFFTfromWav( T, frameSize)
% 程式功能：將時域之資料讀取後依照輸入之音框大小Framing後再行FFT
% 輸入參數說明：
%   T               → 要FFT之陣列檔案
%   frameSize       → 音框大小
% 輸出參數說明：
%   frameF          → 切完音框後之頻域陣列
    %%
%     player = audioplayer( T, FS);
%     playblocking( player);
    frames = floor( size(T, 1)/frameSize);
    frameT = zeros( frameSize, frames);
    frameF = zeros( frameSize, frames);
    for i = 1:frames
        frameT(:, i) = T( frameSize*(i-1)+1:frameSize*i, 1);
    end
    for i = 1:frames
      frameF( :, i) = fft( frameT( :, i), frameSize);  
    end
end