%BDA
%Erismann Marcel
%Test um ein Smith Diagramm aus einer Simulation zu importiern und
%darzustellen

clc;
clear all;


real_imag = csvread('test_smith_real_imag.csv',1,0)
f30=figure(30);
plot(real_imag(:,1), real_imag(:,2), 'b','LineWidth',2);
grid on
hold on;
plot(real_imag(:,3), real_imag(:,4), 'r','LineWidth',2);
legend('real','imag','Location', 'NorthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('real und imaginär Teil')
saveas(f30,'real_imag','fig'); 
    
    
 S = csvread('test_smith_real_imag_7.csv');
     s11 = rfparam(S,1,1);
     figure
     smithchart(s11)