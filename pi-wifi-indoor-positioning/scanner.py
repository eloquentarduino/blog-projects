import json
from rssi import RSSI_Scan
from time import sleep


if __name__ == '__main__':
    scanner = RSSI_Scan('en0')
    lines = []

    while True:
        location = input('Enter location (leave empty to exit): ')

        if not location:
            print('No location entered, exiting...')
            break

        repeat = int(input('How many samples will you take? '))

        for i in range(repeat):
            print('scanning %d/%d' % (i + 1, repeat))
            networks = scanner.getAPinfo(sudo=True)
            rssis = {network['ssid']: network['signal'] for network in networks}
            rssis.update(__location=location)
            lines.append(json.dumps(rssis))
            print(lines[-1])

    print('Here comes the data for port_wifi_indoor_positioning()')
    [print(line) for line in lines]