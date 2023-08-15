# Mustafa Mannan

""" in my religion it is a requirement of faith to pray 5 times a day and one of the requirements for
a prayer to be valid is that the person must pray in the direction of the kaaba which is a holy site in
mecca ( a holy city in saudi arabia) """

""" This program serves to find the correct angle for which the person praying would be facing the kaaba
using geometric calculations and some libraries to get the users longitude and latitude """




import pygame
import sys
import math

import requests



# Initialize pygame
pygame.init()

# Set up the window
window_size = (400, 400)
screen = pygame.display.set_mode(window_size)
pygame.display.set_caption("Compass with Arrow and Angle")

# Colors
WHITE = (255, 255, 255)
BLACK = (0, 0, 0)
RED = (255, 0, 0)

# Function to draw the compass needle pointing to the given angle
def draw_needle(angle):
    needle_length = 150
    x = compass_center[0] + needle_length * math.sin(math.radians(angle))
    y = compass_center[1] - needle_length * math.cos(math.radians(angle))
    pygame.draw.line(screen, RED, compass_center, (x, y), 3)

# Function to draw the text on the screen
def draw_text(text, font, color, x, y):
    surface = font.render(text, True, color)
    screen.blit(surface, (x, y))


#Function to get the Lat,Long using an api
def get_longitude_latitude():
    try:
        # Get public IP address
        ip_response = requests.get('https://api.ipify.org?format=json')
        ip_data = ip_response.json()
        public_ip = ip_data['ip']

        # Get geolocation data based on the public IP
        geolocation_response = requests.get(f'https://ipinfo.io/{public_ip}/json')
        geolocation_data = geolocation_response.json()

        # latitude and longitude
        latitude, longitude = geolocation_data['loc'].split(',')
        return float(latitude), float(longitude)
    except Exception as e:
        raise ValueError(f"Error: {e}")

if __name__ == "__main__":
    try:
        latitude, longitude = get_longitude_latitude()
    except ValueError as ve:
        print(ve)
    compass_center = (window_size[0] // 2, window_size[1] // 2)
    compass_radius = 150




#Converting kaaba's coordinates into radians
xm=math.radians(21.4225)        

ym=math.radians(39.8262)


#converting my coordinates to radians
x=math.radians(latitude)

y=math.radians(longitude)


# Great Circle Bearing formula function
def great_circle(xm,ym,x,y):        
    delta_y = ym - y
    delta_x = x

    # Formula
    angle_rad = math.atan2(math.sin(delta_y) * math.cos(xm),
                           math.cos(x) * math.sin(xm) - math.sin(x) * math.cos(xm) * math.cos(delta_y))

    # Convert the angle from radians to degrees
    angle_deg = math.degrees(angle_rad)

    # angle has to be positive as clockwise 
    angle_deg = (angle_deg + 360) % 360

    return angle_deg
    
angle=great_circle(xm,ym,x,y)


#main loop
def main():
    clock = pygame.time.Clock()

    # Set up compass properties
    compass_center = (window_size[0] // 2, window_size[1] // 2)
    compass_radius = 150

    # Font 
    font = pygame.font.SysFont(None, 20)

    while True:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                pygame.quit()
                sys.exit()

        # Clear the screen
        screen.fill(WHITE)

        # Draw the compass circle
        pygame.draw.circle(screen, BLACK, compass_center, compass_radius, 3)

        # Draw the compass increments (30 degrees) and numbers
        for i in range(0, 360, 30):
            angle_rad = math.radians(i)
            x = compass_center[0] + (compass_radius - 15) * math.sin(angle_rad)
            y = compass_center[1] - (compass_radius - 15) * math.cos(angle_rad)
            pygame.draw.line(screen, BLACK, (x, y), (compass_center[0] + compass_radius * math.sin(angle_rad), compass_center[1] - compass_radius * math.cos(angle_rad)), 2)
            number = str(i) if i > 0 else "360"
            draw_text(number, font, BLACK, x - 10, y + 5)

        # Draw the compass needle pointing to 43 degrees from true north
        draw_needle(angle)

        # Displays the angle
        angle_text = f"Qibla Angle: {angle:.1f} degrees"

        draw_text(angle_text, font, BLACK, window_size[0] // 2 - 60, window_size[1] - 30)

        pygame.display.flip()
        clock.tick(60)


if __name__=="__main__":
    main()











