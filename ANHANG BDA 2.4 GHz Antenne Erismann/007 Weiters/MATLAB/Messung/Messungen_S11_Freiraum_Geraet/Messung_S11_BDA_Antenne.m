% %%
% %S11
% %Dipol 3mm breit
% %im Gerät
% s11_1mm_frei = csvread('s11_Dipol_3mm_geraet.csv',1,0)
% f100=figure(100);
% plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
% legend('S_{11} Messung','Location', 'SouthEast')
% ylabel('Amplitude in [dB]') 
% xlabel('Frequenz in [Hz]')
% title('Messung des  S_{11} Wert einer Dipolantenne 3mm breit im Gerät')
% %saveas(f100,'Messung S11 einer Dipolantenne 3mm breit im Gerät','fig');

%% S11
% Länge = 24.5mm
% Länge = 50.25
% Breite = 3mm
% Dicke = 0.026mm
% Freiraum  und im Gerät
Simulation_frei = csvread('S11_3mm_Freiraum_simulation.csv',1,0) %simulationswerte CSV zuschneiden
Simulation_geraet = csvread('S11_3mm_Geraet_simulation.csv',1,0) %simulationswerte CSV zuschneiden
s11_3mm_geraet = csvread('S11_veraendert.csv',1,0)

grid on
f101=figure(101);

plot(Simulation_frei(:,1).*10^9, Simulation_frei(:,2), 'r','LineWidth',2)
hold on;
plot(Simulation_geraet(:,1).*10^9, Simulation_geraet(:,2), 'b','LineWidth',2);
plot(s11_3mm_geraet(:,1), s11_3mm_geraet(:,2), 'g','LineWidth',2);
legend('S_{11} Frei Raum','S_{11} im Gerät','S_{11} Messung im Gerät','Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Simulation des  S_{11} im Freiraum und dim Gerät eines Dipol 3mm breit')
%saveas(f101,'Vergleich_s11_3mmDipol_Freiraum_Geraet','pdf');

%%
%S11
%Dipol 3mm breit
%im Gerät
%s11_3mm_geraet = csvread('S11_veraendert.csv',1,0)
%f100=figure(100);
plot(s11_3mm_geraet(:,1), s11_3mm_geraet(:,2), 'g','LineWidth',2), grid;
%legend('S_{11} Messung','Location', 'SouthEast')
%ylabel('Amplitude in [dB]')
%xlabel('Frequenz in [Hz]')
%title('Messung des  S_{11} Wert einer Dipolantenne 3mm breit im Gerät')
%saveas(f100,'Messung S11 einer Dipolantenne 3mm breit im Gerät','fig');

