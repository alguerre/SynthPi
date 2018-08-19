%% Test potenciometer
% This is a tool to characterize the voltage fall accross a
% potentiometer. Thus, it is possible to check the connection and
% behaviour. The measurements are done through the analog in pins of an
% arduino board.

%% User parameters
Vref = 3.3;  % reference voltage in volts
analog_pin = 'A0';
margin_low = 0.05;  % margin to determine if it in maximum or minimum position
margin_high = 0.90;
type = 'log';

%% Arduino initialization
clear a arduino
arduino = arduino();

%% Test
Vinit = readVoltage(arduino, analog_pin);

% Starting check
if (Vinit > Vref*margin)
    fprintf(1, 'Please, set the pontentiometer in minimum resistance mode.\n'); 
    fprintf(1, 'Current value:       ');
    while (Vinit > Vref*margin)
        Vinit = readVoltage(arduino, analog_pin);
        fprintf(1, '\b\b\b\b\b\b%.4f', Vinit);
        pause(0.05);
    end
end

% Test
fprintf(1,'\n');  % blank lin
fprintf(1,'When the test start move continously the potentiometer to its maximum resistance mode.\n');
fprintf(1,'Test is starting in: ');
fprintf(1,'3');
pause(1);
fprintf(1,'\b2');
pause(1);
fprintf(1,'\b1');
pause(1);
fprintf(1,'\b0!');
pause(1);
fprintf(1, '\nTest in progress. Current value:       ');

voltage_record = -1 * ones(50000,1);
Vmeas = Vinit;
i = 0;
while (Vmeas < Vref*margin_high)
    i = i + 1;
    Vmeas = readVoltage(arduino, analog_pin);
    voltage_record(i) = Vmeas;
    fprintf(1, '\b\b\b\b\b\b%.4f', Vmeas);
    pause(0.05);
end
fprintf(1,'\n');  % blank line

% Plot results
voltage_record = voltage_record(1:i, 1);
figure
plot(voltage_record, 'k', 'LineWidth', 4)
ylabel('Voltage (V)')
xlabel('Measurement index')
hline = refline(0, Vref);
hline.LineWidth = 3;

if (strcmp(type, 'log'))
    figure
    plot(log(voltage_record), 'k', 'LineWidth', 4)
    ylabel('Log(Voltage)')
    xlabel('Measurement index')
    hline = refline(0, log(Vref));
    hline.LineWidth = 3;

end
