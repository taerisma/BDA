[xyx xyy xzx xzz] = starlab2polar('Daten3oder5.txt', 'a1.txt', 'a2.txt');
figure
subplot(211)
plot(xyx,xyy)
axis('equal')
xlabel('x-Achse')
ylabel('y-Achse')
subplot(212)
plot(xzx,xzz)
xlabel('x-Achse')
ylabel('z-Achse')
subplot(211)
legend('xy-Ebene')
grid on
subplot(212)
legend('xz-Ebene')
grid on
axis('equal')