%%
%Effizienz
%Dipol 3mm breit
%im Gerät
Effizienz = csvread('Effizienz3oder5_veraendert.csv',1,0)
f200=figure(200);
plot(Effizienz(:,1), Effizienz(:,2).*100, 'r','LineWidth',2), grid;
legend('Effizienz','Location', 'SouthWest')
ylabel('Effizienz [%]')
xlabel('Frequenz in [Hz]')
title('Effizienz eienr Dipolantenne')
saveas(f200,'Effizienz_Dipolatenne','fig');