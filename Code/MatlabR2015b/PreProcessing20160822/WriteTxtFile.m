% �{���\��G�N�x�}��Ƽg�Jtxt�ɮ�
% ��J�Ѽƻ����G
%   file            �� �n�g�J��txt�ɦW
%   matrix          �� �N��}�C��Ƽg�Jtxt��
%   ClearTxtContent �� �O�_�M��txt�ɤ��Ҧ���ƦA�N�}�C��Ƽg�J�A����true�h�M���Afalse�h���M��

function WriteTxtFile(file, matrix, ClearTxtContent)
    if ClearTxtContent, 
        fid = fopen(file, 'wt');%'w' -> clear the content of the txt file
    else 
        fid = fopen(file, 'a');%'w' -> open file for writing; discard existing contents
    end
    [ m, n] = size(matrix);
    fprintf(fid, '\n\t%4d\t%4d\n', m, n);
    for i=1:m
        for j=1:n        
            fprintf(fid, '%e\t', matrix(i,j));        
        end
         fprintf(fid, '\n');
    end
    fclose(fid);
end

