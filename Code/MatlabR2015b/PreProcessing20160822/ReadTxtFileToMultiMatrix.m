function matrixList = ReadTxtFileToMultiMatrix(file)
% 程式功能：將txt檔案讀取為多個矩陣資料
% 輸入參數說明：
%   file            → 要讀取的txt檔名
% 輸出參數說明：
%   matrixList      → 多個矩陣資料，此資料結構為java.util.LinkedList
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

