function matrix = ReadTxtFile(file )
% �{���\��G�Ntxt�ɮ�Ū�����x�}���
% ��J�Ѽƻ����G
%   file            �� �nŪ����txt�ɦW
%%
    fid = fopen(file, 'r');
    s = fscanf( fid, '%d', 2);
    m = fscanf(fid, '%le');        
    matrix = zeros(s(1), s(2));
    for i = 1:s(1)
        for j = 1:s(2)
            matrix( i, j) = m((i-1)*s(2) + j);
        end
    end
    fclose(fid);
end

