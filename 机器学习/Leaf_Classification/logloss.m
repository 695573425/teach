function [X] = logloss()


    data = csvread('submission2.csv',1,0);
    id = data(:,1);
    X = data(:,2:end);
    [m,n] = size(X);
    y = zeros(m,2);
    for i = 1:m
        for j = 1:n
            if(X(i,j)>y(i,2))
                y(i,2) = X(i,j);
                y(i,1) = j;
            end
        end
    end
    
    data = csvread('submission.csv',1,0);
    id = data(:,1);
    X = data(:,2:end);
    [m,n] = size(X);
        y1 = zeros(m,2);
    for i = 1:m
        for j = 1:n
            if(X(i,j)>y1(i,2))
                y1(i,2) = X(i,j);
                y1(i,1) = j;
            end
        end
    end
    Z = zeros(m,3);
    k=1;
    for i = 1:m
        if y1(i,1) ~= y(i,1)
            Z(k,1) = i;
            Z(k,2) = y(i,1);
            Z(k,3) = y1(i,1);
            k = k+1;
        end
    end
%     M = zeros(56,2);
%       for i = 1:20
%           M(i,1) =Z(i,1);
%           M(i,2) = X(Z(i,1),Z(i,2));
%       end
%     [~,a] = sort(M(:,2));
% 
%     temp = 0;
%     for i = 1:30
%         j = a(i);
%         temp = X(Z(j,1),Z(j,2));
%         X(Z(j,1),Z(j,2)) = X(Z(j,1),Z(j,3));
%         X(Z(j,1),Z(j,3)) = temp;
%     end

    loss =0;
    for i = 1:m

        loss = loss + log(X(i,y(i,1)));
    end
    loss = loss/(-m);
    
   

end