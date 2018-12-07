% 程式功能：將矩陣資料寫入txt檔案
% 輸入參數說明：
%   file            → 要寫入的txt檔名
%   matrix          → 將何陣列資料寫入txt檔
%   ClearTxtContent → 是否清除txt檔中所有資料再將陣列資料寫入，此格true則清除，false則不清除

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

