function matrixList = ReadTxtFileToMultiMatrix(file)
% �{���\��G�Ntxt�ɮ�Ū�����h�ӯx�}���
% ��J�Ѽƻ����G
%   file            �� �nŪ����txt�ɦW
% ��X�Ѽƻ����G
%   matrixList      �� �h�ӯx�}��ơA����Ƶ��c��java.util.LinkedList
%%
    fid = fopen( file, 'r');
    matrixList = java.util.LinkedList;
    iter = matrixList.listIterator;
    layerNum = fscanf( fid, '%d', 1);
    for layer = 1:layerNum
        s = fscanf( fid, '%d', 2);
        m = fscanf(fid, '%le', s(1)*s(2));        
        matrix = zeros( s(1), s(2));
        for i = 1:s(1)
            for j = 1:s(2)
                matrix( i, j) = m((i-1)*s(2) + j);
            end
        end
        iter.add(matrix);
    end    
    fclose(fid);
end

