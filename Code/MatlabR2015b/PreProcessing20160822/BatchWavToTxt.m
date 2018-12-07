function [] = BatchWavToTxt( sizeOfFrame, numOfFrame, sampleNum)
% 程式功能：依照NOIZEUS DataSet中的音訊資料製作其特徵資料集
% 輸入參數說明：
%   sizeOfFrame     → 音框大小
%   numOfFrame      → 輸入DNN學習的資料需要組合的音框數量
%   sampleNum       → 於NOIZEUS DataSet中，需要作為特徵資料集的樣本數量，最大30。
% 輸出參數說明：
%   無輸出參數，但是最終將於norF以及phaF寫出特徵資料集合，皆為txt資料，此外將另外輸出FS.txt表示各個音訊樣本的取樣頻率(Sample rate)。
 %%
    FS = [];

    folderName = 'clean/';
    for fileNum = 1:sampleNum
        if fileNum < 10
            fileName = num2str(fileNum,'sp0%d');
        else
            fileName = num2str(fileNum,'sp%d');
        end
        [magF, phaF, fs]=ExtractFeature( strcat( 'NOIZEUS DataSet/', folderName, fileName,'.wav'), sizeOfFrame);
        if size(magF,2) ~= size(phaF, 2)
            fprintf('%s以及%s\n', strcat('norF/', folderName, fileName, '.txt'), strcat('phaF/', folderName, fileName, '.txt'));
        end
        magF = ReshapeMatrix( magF, numOfFrame);
        phaF = ReshapeMatrix( phaF, numOfFrame);
        WriteTxtFile(strcat('norF/', folderName, fileName, '.txt'), magF, 1);
        WriteTxtFile(strcat('phaF/', folderName, fileName, '.txt'), phaF, 1);
        FS = [ FS fs];
    end

%% 
    noiseType = char('airport_', 'babble_', 'car_', 'exhibition_', 'restaurant_', 'station_', 'street_', 'train_');
    noisedB = char('0dB/', '5dB/', '10dB/', '15dB/');
    noiseSN = char('sn0', 'sn5', 'sn10', 'sn15');
    for type = 1:size( noiseType, 1)
        for dB = 1:size( noisedB, 1)  
            folderName = strcat( noiseType( type, :), noisedB( dB, :), noisedB( dB, :));
            for fileNum = 1:sampleNum
                if fileNum < 10
                    fileName = num2str(fileNum,'sp0%d_');
                else
                    fileName = num2str(fileNum,'sp%d_');
                end
                fileName = strcat( fileName, noiseType( type, :), noiseSN( dB, :));
                [ magF, phaF, fs] = ExtractFeature( strcat( 'NOIZEUS DataSet/', folderName, fileName,'.wav'), sizeOfFrame);
                if size(magF,2) ~= size(phaF, 2)
                    fprintf('%s以及%s\n', strcat('norF/', folderName, fileName, '.txt'), strcat('phaF/', folderName, fileName, '.txt'));
                end
                magF = ReshapeMatrix( magF, numOfFrame);
                phaF = ReshapeMatrix( phaF, numOfFrame);
                WriteTxtFile(strcat('norF/', folderName, fileName, '.txt'), magF, 1);
                WriteTxtFile(strcat('phaF/', folderName, fileName, '.txt'), phaF, 1);
                FS = [ FS fs];
                fprintf('%s以及%s\n', strcat('norF/', folderName, fileName, '.txt'), strcat('phaF/', folderName, fileName, '.txt'));
            end
        end
    end
    WriteTxtFile('FS.txt', FS, 1);
end


