function [ T ] = WaveformReconstruct( magF, phaF)
% �{���\��GExtractFeature�{�������Ĥ@�B�J�᪺Inverse Function�C
%% 
    magF = power( 10, magF);
    magF = magF-1;
    frameF = complex(magF.*cos(phaF), magF.*sin(phaF));
%%
    T = GetTfromFramingF( frameF );
end

function T = GetTfromFramingF( frameF )
% �{���\��G�N�Q�������ت��W����ifft�᭫�խ��ح�l�ɰ�}�C
% ��J�Ѽƻ����G
%   T               �� �nFFT���}�C�ɮ�
%   frameSize       �� ���ؤj�p
% ��X�Ѽƻ����G
%   frameF          �� �������ثᤧ�W��}�C
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
% �{���\��G�N�Q�������ت��W����ifft�᭫�խ��ح�l�ɰ�}�C
% ��J�Ѽƻ����G
%   T               �� �nFFT���}�C�ɮ�
%   frameSize       �� ���ؤj�p
% ��X�Ѽƻ����G
%   frameF          �� �������ثᤧ�W��}�C
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

