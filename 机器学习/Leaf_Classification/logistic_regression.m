function [P] = logistic_regression()

    [label,X,y,test] = Leaf_Classification();
    [m,n] = size(X);
    k = length(label);
    X = [ones(m,1) X];
    
    
    all_w = zeros(n+1,k);

    for i = 1 : k 
        y0 = zeros(m,1);
        for j = 1 : m
            if strcmp(char(y(j)),char(label(i)))
                y0(j) = 1;
            end
        end
        [all_w(:,i),~] = Newton(X,y0,0);
        
    end

    
    m1 = size(test,1);
    test = [ones(m1,1) test];
    M = test * all_w;
    
    P = zeros(m1,k);
    for i = 1 : m1
        for j = 1 : k
            P(i,j) = exp(M(i,j));
        end
        pi = sum(P(i,:));
        P(i,:) = P(i,:)/pi;  
    end
    

   

    
end

function [label,train_data,train_label,test_data] = Leaf_Classification()

    fid = fopen('sample_submission.csv');
    label = textscan(fid,'%s','delimiter',','); 
    label = label{1}(2:100);
    fclose(fid);
    
    fid = fopen('train.csv');
    train_label = textscan(fid,'%*d %s %*[^\n]  ','delimiter',',','HeaderLines',1);
    train_label = train_label{1};
    fclose(fid);
    
    train_data = csvread('train.csv',1,2);
    test_data = csvread('test.csv',1,1);
    
    
end

%sigmoid函数
function [g] = sigmoid(z)
    g = 1 ./ (1 + exp(-z));
end

%损失函数及其梯度
%lambda为正则项参数，为0时表示不加正则项
function [J,grad] = Loss(w,X,y,g,lambda)
    m = size(y,1);
    J = 1/m * sum((-y .* log(g)) - (1-y) .* log(1-g))...
        +lambda/(2*m) * sum(w(2:end).^2);
%     grad = zeros(size(w));
%     for i = 1:size(w)
%         if i == 1
%             grad(i) = 1/m * sum((g-y)'*X(:,i));
%         else
%             grad(i) = 1/m * sum((g-y)'*X(:,i)) + lambda/m *w(i);
%         end
%     end
    error = g-y;
    grad = X'*error/m + lambda/m*w;
    
    grad(1) = error'*X(:,1)/m;

end


%海森矩阵
function [H] = Hessian(X,g)
    m = size(X,1);
    H = (1/m) * X' * diag(g) * diag(1-g) * X;
end


%牛顿法
function [w,k] = Newton(X,y,lambda)
    w = zeros(size(X,2),1);
    k=1;
    g = sigmoid(X*w);
    [J_pre,grad] = Loss(w,X,y,g,lambda);
    H = Hessian(X,g);
    w = w - H\grad;
    g = sigmoid(X*w);
    [J,grad] = Loss(w,X,y,g,lambda);
 
    while(abs(J-J_pre) > 10e-6)   
        k = k+1;
        H = Hessian(X,g);
      
        w = w - H\grad;
        J_pre = J;
        g = sigmoid(X*w);
        [J,grad] = Loss(w,X,y,g,lambda);

    end  

end



    