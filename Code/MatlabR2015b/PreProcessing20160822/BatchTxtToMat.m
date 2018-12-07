function [T] = BatchTxtToMat( sizeOfFrame, sampleNum)
% �{���\��G�N�S�x��ƶ������(norF�H��phaF�������)���s�զX�����T���
% ��J�Ѽƻ����G
%   sizeOfFrame     �� ���ؤj�p
%   sampleNum       �� �S�x��ƶ����˥��ƶq�A�̤j30�C
% ��X�Ѽƻ����G
%   T               �� ���T��ơA���Ƶ��c���@��cell�C
 %% 
    folderNum = 33;
    folderName = 'clean/';
    T = cell( folderNum, sampleNum);
    for fileNum = 1:sampleNum
        if fileNum < 10
            fileName = num2str(fileNum,'sp0%d');
        else
            fileName = num2str(fileNum,'sp%d');
        end
        magF = ReadTxtFile(strcat('norF/', folderName, fileName, '.txt'));
        phaF = ReadTxtFile(strcat('phaF/', folderName, fileName, '.txt'));
        numOfFrame = floor(size( magF, 1)/sizeOfFrame);
        magF = ReshapeMatrix( magF, 1/numOfFrame);
        phaF = ReshapeMatrix( phaF, 1/numOfFrame);
        t = RevertTfromFeatureMat( magF, phaF);
        T{ 1, fileNum} = t;
    end

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
                fileName = strcat(fileName, noiseType( type, :), noiseSN( dB, :));
                magF = ReadTxtFile(strcat('norF/', folderName, fileName, '.txt'));
                phaF = ReadTxtFile(strcat('phaF/', folderName, fileName, '.txt'));
                numOfFrame = floor(size( magF, 1)/sizeOfFrame);
                magF = ReshapeMatrix( magF, 1/numOfFrame);
                phaF = ReshapeMatrix( phaF, 1/numOfFrame);
                t = WaveformReconstruct( magF, phaF);
                T{(type-1)*size( noisedB, 1)+dB+1, fileNum} = t;
                fprintf('%s�H��%s\n', strcat('norF/', folderName, fileName, '.txt'), strcat('phaF/', folderName, fileName, '.txt'));
            end
        end
    end
    
    
end