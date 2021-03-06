%BDA 
%Erismann Marcel
%Vergleich S11 aus Simulation im Freiraum und mit Kunststoff
%Vergleich des Realteils und Imagin�rteil im Freiraum, mit ABS und ABS St�cken
%Loop Antenne
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
close all;
clear all;
%sucht die zu oeffneden Fils im selben Ordner wie das skrip
fileItem = matlab.desktop.editor.getActive;
cd(fileparts(fileItem.Filename));

Simulation_Loop_frei = csvread('S11_Loop_frei.csv',1,0) 
Simulation_Loop_1ABS = csvread('S11_Loop_1ABS.csv',1,0) 
Simulation_Loop_2ABS = csvread('S11_Loop_2ABS.csv',1,0) 

f60=figure(60); 
plot(Simulation_Loop_frei(:,1), Simulation_Loop_frei(:,2), 'r')
hold on;
plot(Simulation_Loop_1ABS(:,1), Simulation_Loop_1ABS(:,2), 'b');
plot(Simulation_Loop_2ABS(:,1), Simulation_Loop_2ABS(:,2), 'g'), grid;
legend('S_{11} Frei Raum','S_{11} mit ABS','S_{11} mit 2 ABS', 'Location', 'SouthWest')
ylabel('Amplitude in [dB]') 
xlabel('Frequenz in [GHz]')
title('Simulation des  |S_{11}| einer Loop Antnne im Freiraum, mit einem und zwei ABS St�cken')
saveas(f60,'Vergleich_S11_Loop','pdf');

%
%%
%Real und Imgin�rteil
%Loop Antenne
%Im Freiraum mit ABS und 2ABS St�cken
Impedanz_Loop_frei = csvread('Impedanz_Loop_frei.csv',1,0) 
Impedanz_Loop_1ABS = csvread('Impedanz_Loop_1ABS.csv',1,0) 
Impedanz_Loop_2ABS = csvread('Impedanz_Loop_2ABS.csv',1,0) 
f70=figure(70); 
plot(Impedanz_Loop_frei(:,1), Impedanz_Loop_frei(:,2), 'r')
grid on;
hold on;
plot(Impedanz_Loop_frei(:,3), Impedanz_Loop_frei(:,4), 'b');
plot(Impedanz_Loop_1ABS(:,1), Impedanz_Loop_1ABS(:,2), 'g')
plot(Impedanz_Loop_1ABS(:,3), Impedanz_Loop_1ABS(:,4), 'k');
plot(Impedanz_Loop_2ABS(:,1), Impedanz_Loop_2ABS(:,2), 'y')
plot(Impedanz_Loop_2ABS(:,3), Impedanz_Loop_2ABS(:,4), 'm');
legend('Realteil im Freien','Imagin�rteil im Freien', 'Realteil mit ABS','Imagin�rteil mit ABS','Realteil mit 2ABS','Imagin�rteil mit 2ABS','Location', 'NorthEast')
ylabel('Impedanz [Ohm]') 
xlabel('Frequenz in [GHz]')
title('Impedanz der Loop Antenne im Freiraum, mit einem und zwei ABS St�cken')
saveas(70,'Vergleich_Impedanz_Loop','pdf');