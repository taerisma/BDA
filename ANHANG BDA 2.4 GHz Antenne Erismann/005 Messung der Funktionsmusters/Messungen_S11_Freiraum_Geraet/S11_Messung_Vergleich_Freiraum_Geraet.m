%BDA 
%Erismann Marcel
%Vergleich S11 aus Messungen
%Die Antennen werden im Freiraum und im Gerät gemessen
%Dipol Antenne
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
%sucht die zu oeffneden Fils im selben Ordner wie das skrip
fileItem = matlab.desktop.editor.getActive;
cd(fileparts(fileItem.Filename));

%% S11 
% erster Versuch
%3mm oder 5mm breit
%im Gehäuse
load('NameMESSUNG.dat')%Messung S11 1.95E+9 Hz bis 2.95E+9Hz bis 200 Werte
%Simulation = csvread('simSIM.csv',1,0) %simulationswerte CSV zuschneiden
NameMESSUNG2x= NameMESSUNG(14:201,1); %Mesung die Werrte zuschneiden x
NameMESSUNG2y=NameMESSUNG(14:201,2);  %Mesung die Werrte zuschneiden y
f10=figure(10); 
plot(NameMESSUNG2x,NameMESSUNG2y, 'r')
grid on
%hold on;
%plot(Simulation(:,1).*10^9, Simulation(:,2), 'b'), grid;
legend('S_{11} Messung','Location', 'SouthEast')  %'S_{11} Simulation',
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne im Gehäuse')
saveas(f10,'erste  S11 Messung einer Dipolantenne im Gehaeuse','fig'); 



%%
%S11
%Dipol 1mm breit
s11_1mm_frei = csvread('s11Freiraum1mmKoma.csv',1,0)
f11=figure(11);
plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
legend('S_{11} Messung','Location', 'NorthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne im Freiraum')
saveas(f11,'Messung S11 einer 1mm breiten Dipolantenne','fig'); 
%%
%S11
%Dipol 1mm breit mit Dachkapazität
s11_1mm_frei = csvread('s11 1mm dach 1mmkompensiert freiraum.csv',1,0)
f12=figure(12);
plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
legend('S_{11} Messung','Location', 'NorthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne mit Dachkapazität im Freiraum ')
saveas(f12,'Messung S11 einer Dipolantenne mit Dach 1mm','fig'); 
%%
%S11
%Dipol 
%im Geraet
s11_1mm_frei = csvread('s11_imGeraet_V002_phi50.csv',1,0)
f13=figure(13);
plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
legend('S_{11} Messung','Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne im Gerät ')
saveas(f13,'Messung S11 einer Dipolantenne im Geraet','fig'); 
%%
%S11
%Dipol 3mm breit
%im Geraet
s11_1mm_frei = csvread('s11 im geraet 3mm.csv',1,0)
f14=figure(14);
plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
legend('S_{11} Messung','Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne 3mm breit im Gerät ')
saveas(f14,'Messung S11 einer Dipolantenne 3mm breit im Geraet','fig'); 
%%
%v003
%S11
%Dipol 3mm breit
%25mm pro Dipolarm
%eher Freiraum
s11_1mm_frei = csvread('s11v003_3mm_25lang_alt_v003.csv',1,0)
f15=figure(15);
plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
legend('S_{11} Messung','Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne 3mm breit')
saveas(f15,'Messung S11 einer Dipolantenne 3mm breit','fig'); 
%%
%v002
%S11
%Dipol 3mm breit
%eher im Gerät
%vermutung seleb Antenne wie in f15 aber im Gerät
s11_1mm_frei = csvread('s11_v002_alt_Dipol3mm_V002.csv',1,0)
f16=figure(16);
plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
legend('S_{11} Messung','Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne 3mm breit v002')
saveas(f16,'Messung S11 einer Dipolantenne 3mm breit v002','fig'); 

%%
%S11
%Dipol 3mm breit
%im Gerät
s11_1mm_frei = csvread('s11_Dipol_3mm_geraet.csv',1,0)
f17=figure(17);
plot(s11_1mm_frei(:,1), s11_1mm_frei(:,2), 'b','LineWidth',2), grid;
legend('S_{11} Messung','Location', 'SouthEast')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [Hz]')
title('Messung des  S_{11} Wert einer Dipolantenne 3mm breit im Gerät')
saveas(f17,'Messung S11 einer Dipolantenne 3mm breit im Gerät','fig'); 
%%
% %% S11
% % Länge = 24.5mm
% % Breite = 5mm
% % Dicke = 0.035mm
% % im Gerät
% 
% load('NameMESSUNG.dat')%Messung S11 1.95E+9 Hz bis 2.95E+9Hz bis 200 Werte
% Simulation = csvread('S11_simulation_5mm_Dipol_Freiraum.csv',1,0) %simulationswerte CSV zuschneiden
% NameMESSUNG2x= NameMESSUNG(14:201,1); %Mesung die Werrte zuschneiden x
% NameMESSUNG2y=NameMESSUNG(14:201,2);  %Mesung die Werrte zuschneiden y
% f2=figure(2); 
% plot(NameMESSUNG2x,NameMESSUNG2y, 'r')
% hold on;
% plot(Simulation(:,1).*10^9, Simulation(:,2), 'b'), grid;
% legend('S_{11} Messung','S_{11} Simulation', 'Location', 'SouthEast')
% ylabel('Amplitude in [dB]') 
% xlabel('Frequenz in [Hz]')
% title('Verglech Messung und Simulation des  S_{11} im Gerät')
% saveas(f2,'Vergleich_s11_5mmDipol','fig');
% 
% 
% 
% 
% %% S11
% % Länge = 24.5mm
% % Breite = 5mm
% % Dicke = 0.026mm
% % Freiraum
% 
% %load('.dat')%Messung S11 1.95E+9 Hz bis 2.95E+9Hz bis 200 Werte
% Simulation = csvread('S11_5mm_Geraet_simulation.csv',1,0) %simulationswerte CSV zuschneiden
% NameMESSUNG2x= NameMESSUNG(14:201,1); %Mesung die Werrte zuschneiden x
% NameMESSUNG2y=NameMESSUNG(14:201,2);  %Mesung die Werrte zuschneiden y
% f3=figure(3); 
% plot(NameMESSUNG2x,NameMESSUNG2y, 'r')
% hold on;
% plot(Simulation(:,1).*10^9, Simulation(:,2), 'b'), grid;
% legend('S_{11} Messung','S_{11} Simulation', 'Location', 'SouthEast')
% ylabel('Amplitude in [dB]') 
% xlabel('Frequenz in [Hz]')
% title('Verglech Messung und Simulation des  S_{11} im Freiraum')
% saveas(f3,'Vergleich_s11_5mmDipol','fig');
