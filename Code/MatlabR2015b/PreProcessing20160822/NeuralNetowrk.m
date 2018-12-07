function [ output, err] = NeuralNetowrk( weightsList, input, target)
% �{���\��G�̷ӵ������v���ΥؼСA���o��NeuralNetowrk����X�ο��~�v(Error rate)
% ��J�Ѽƻ����G
%   weightsList            �� NeuralNetowrk���v���A����Ƶ��c�����Ojava.util.LinkedList
%   input                  �� NeuralNetowrk����J
%   target                 �� NeuralNetowrk���ؼ�
% ��X�Ѽƻ����G
%   output                 �� NeuralNetowrk����X
%   err                    �� NeuralNetowrk�����~�v
%%
    output = input;
    for i=0:(weightsList.size)-1
        output = weightsList.get(i)*output;
        if i<(weightsList.size)-1
            output = 1.0 ./ (1.0 + exp(-output));
        end
    end
    err = target-output;
end

