%% Get data
data_csv = csvread('data.csv');
time_csv = M(:,1);
value_csv = M(:,2);

%% Reference
freq = 440.0;  % freq in Hz
time_ref = time_csv;
value_ref = sin(2*pi*freq*time_ref);

%% Compare plots
n_points = 100;
figure (1)
plot(time_ref(1:n_points), value_ref(1:n_points), 'LineWidth', 3)
hold on
plot(time_csv(1:n_points), value_csv(1:n_points), 'r')
hold off
