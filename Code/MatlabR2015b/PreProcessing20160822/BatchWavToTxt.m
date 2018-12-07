function [] = BatchWavToTxt( sizeOfFrame, numOfFrame, sampleNum)
% �{���\��G�̷�NOIZEUS DataSet�������T��ƻs�@��S�x��ƶ�
% ��J�Ѽƻ����G
%   sizeOfFrame     �� ���ؤj�p
%   numOfFrame      �� ��JDNN�ǲߪ���ƻݭn�զX�����ؼƶq
%   sampleNum       �� ��NOIZEUS DataSet���A�ݭn�@���S�x��ƶ����˥��ƶq�A�̤j30�C
% ��X�Ѽƻ����G
%   �L��X�ѼơA���O�̲ױN��norF�H��phaF�g�X�S�x��ƶ��X�A�Ҭ�txt��ơA���~�N�t�~��XFS.txt��ܦU�ӭ��T�˥��������W�v(Sample rate)�C
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
            fprintf('%s�H��%s\n', strcat('norF/', folderName, fileName, '.txt'), strcat('phaF/', folderName, fileName, '.txt'));
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
                    fprintf('%s�H��%s\n', strcat('norF/', folderName, fileName, '.txt'), strcat('phaF/', folderName, fileName, '.txt'));
                end
                magF = ReshapeMatrix( magF, numOfFrame);
                phaF = ReshapeMatrix( phaF, numOfFrame);
                WriteTxtFile(strcat('norF/', folderName, fileName, '.txt'), magF, 1);
                WriteTxtFile(strcat('phaF/', folderName, fileName, '.txt'), phaF, 1);
                FS = [ FS fs];
                fprintf('%s�H��%s\n', strcat('norF/', folderName, fileName, '.txt'), strcat('phaF/', folderName, fileName, '.txt'));
            end
        end
    end
    WriteTxtFile('FS.txt', FS, 1);
end


