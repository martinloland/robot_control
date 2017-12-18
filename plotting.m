clc, clear, close
file = importdata('export.csv');
data = file.data;
percentage = data(:,1);
force = data(:,5);
plot(percentage,force)
title('Joint 1 force magnitude')
xlabel('Animation percentage [\tau]')
ylabel('Joint force [N]')