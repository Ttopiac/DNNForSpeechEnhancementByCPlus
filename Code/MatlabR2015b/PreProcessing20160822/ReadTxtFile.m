function matrix = ReadTxtFile(file )
% 程式功能：將txt檔案讀取為矩陣資料
% 輸入參數說明：
%   file            → 要讀取的txt檔名
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

