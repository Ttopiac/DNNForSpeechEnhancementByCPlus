function [magF, phaF, FS] = ExtractFeature( fileName, frameSize)
% �{���\��G�Nclean sample��Matrix����Ƹg�L�H�U�B�J�B�z
%           �Ĥ@�B�J�GŪ��wav�ɮ׿�X�ɰ��ƥH��sample rate
%           ����B�J�G   �N�ɰ��Ƥ����ƭӭ��ؤj�p��frameSize������    
%                        �N�C�ӭ��ذ��ť߸��ഫ���W����
%                        �N�W����(��complex number)�ഫ��magnitude�H��phase
%                        �Nmagnitude��ƥ[ 1 ���log
% ��J�Ѽƻ����G
%   fileName        �� �nŪ����wav�ɦW�H�έn�g�J��txt�ɦW (���]�A���ɦW)
%   frameSize       �� ���ؤj�p
% ��X�Ѽƻ����G
%   norF            �� �g�L�W�z�B�J�B�z�L�ᤧ���T�}�C
%   phaF            �� �g�Lfft�B�J�B�z�L�ᤧphase�}�C
%   FS              �� sampling rate(�����W�v)
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
% �{���\��G�Ncomplex variables����phase��magnitude���X
% ��J�Ѽƻ����G
%   frameF          �� ���[complex variables���}�C
% ��X�Ѽƻ����G
%   phaF          �� phase
%   magF          �� magnitude
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
% �{���\��G�N�ɰ줧���Ū����̷ӿ�J�����ؤj�pFraming��A��FFT
% ��J�Ѽƻ����G
%   T               �� �nFFT���}�C�ɮ�
%   frameSize       �� ���ؤj�p
% ��X�Ѽƻ����G
%   frameF          �� �������ثᤧ�W��}�C
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