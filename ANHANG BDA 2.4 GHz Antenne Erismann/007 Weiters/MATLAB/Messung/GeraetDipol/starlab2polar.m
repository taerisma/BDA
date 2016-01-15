function [xyx xyy xzx xzz] = starlab2polar( filename, xy_output, xz_output, theta_const, phi_const)

% data file must have only 3 columns.

% import data
delimiter = '\t';
startRow = 4;
formatSpec = '%f%f%f%[^\n\r]';
fileID = fopen(filename,'r');
textscan(fileID, '%[^\n\r]', startRow-1, 'ReturnOnError', false);
dataArray = textscan(fileID, formatSpec, 'Delimiter', delimiter, 'EmptyValue' ,NaN,'ReturnOnError', false);
fclose(fileID);
Phi = dataArray{:, 1};
Theta = dataArray{:, 2};
r = dataArray{:, 3};

% dB?
if min(r) < 0
    fprintf('0ffset=%f\n', min(r));
    r = r - min(r);
else
    r = 10*log10(r);
    fprintf('0ffset=%f\n', min(r));
    r = r - min(r);
end

% theta const given?
if nargin >= 4
    k1 = theta_const;
else
    k1 = pi/2;
end

th = min(abs(Theta-k1));
ind = find(abs(Theta-k1)<=th);
phitmp1 = Phi(ind);
rtmp1 = r(ind);
ind = find(abs(Theta+k1)<=th);
phitmp2 = Phi(ind)+pi;
rtmp2 = r(ind);
phitot = [phitmp1 ; phitmp2; phitmp1(1)]+pi;
rr = [rtmp1 ; rtmp2; rtmp1(1)];
x = cos(phitot).*rr;
y = sin(phitot).*rr;
A = [x y];
output = fopen(xy_output, 'w');
fprintf(output, 'x   y\n');
for n = 1:size(A,1)
    fprintf(output, '%f ', A(n, :));
    fprintf(output, '\n');
end
fclose(output);

% phi const given?
if nargin == 5
    k2 = phi_const;
else
    k2 = 0;
end

th = min(abs(Phi-k2));
ind = find(abs(Phi-k2)<=th);
ang = Theta(ind)+pi/2;
rr = r(ind);
x = cos(ang).*rr;
y = sin(ang).*rr;
x = [x; x(1)];
y = [y; y(1)];
B = [-x y];
output = fopen(xz_output, 'w');
fprintf(output, 'x   z\n');
for n = 1:size(A,1)
    fprintf(output, '%f ', B(n, :));
    fprintf(output, '\n');
end
fclose(output);

figure(1);
plot(A(:,1),A(:,2), B(:,1),B(:,2))
grid on
legend(sprintf('theta=%f', k1), sprintf('phi=%f', k2));

xyx = A(:,1);
xyy = A(:,2);
xzx = B(:,1);
xzz = B(:,2);
end

