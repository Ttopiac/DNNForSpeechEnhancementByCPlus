function [ output, err] = NeuralNetowrk( weightsList, input, target)
% 程式功能：依照給予的權重及目標，取得此NeuralNetowrk的輸出及錯誤率(Error rate)
% 輸入參數說明：
%   weightsList            → NeuralNetowrk的權重，此資料結構必須是java.util.LinkedList
%   input                  → NeuralNetowrk的輸入
%   target                 → NeuralNetowrk的目標
% 輸出參數說明：
%   output                 → NeuralNetowrk的輸出
%   err                    → NeuralNetowrk的錯誤率
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

