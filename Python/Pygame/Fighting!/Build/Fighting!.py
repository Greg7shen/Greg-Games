"""
    The game itself has no meaning.
    I just made it for fun and more
    importantly, practicing python skills.
"""

# Import relevant modules, otherwise we cannot use anything
# The pygame.locals plays an important role in providing constant
# I use os module to get parent directory
# The math module is to use abs()
import pygame
from pygame.locals import *
import os
import math

# --------------------------SET SCREEN------------------------------
pygame.init()
width, height = 800, 600
screen = pygame.display.set_mode((width, height), RESIZABLE)
# The parent directory stores the absolutely path of Fight folder
parent_directory = os.path.abspath(os.path.dirname(os.getcwd()))
pygame.display.set_caption("Fight")
icon = pygame.image.load(parent_directory + r'\V\icon.jpg')
pygame.display.set_icon(icon)


# ---------------------------CLASS----------------------------------
class Player(pygame.sprite.Sprite):
    def __init__(self, images, index):
        # The index distinguishes the player
        pygame.sprite.Sprite.__init__(self)

        # Create all images of block and resize it
        # Note that images is a dictionary which store the address of image
        self.image = dict()
        # In order to move continuously, the 'walk' property must be a list
        self.image['walk'] = []
        # Total 3 images
        for i in range(3):
            temp_surface = pygame.image.load(images['walk' + str(i)])
            self.image['walk'].append(pygame.transform.scale(temp_surface, (60, 90)))
        self.image['attack'] = pygame.image.load(images['attack'])
        self.image['attack'] = pygame.transform.scale(self.image['attack'], (60, 90))
        self.image['injured'] = pygame.image.load(images['injured'])
        self.image['injured'] = pygame.transform.scale(self.image['injured'], (60, 90))
        self.image['health'] = pygame.image.load(images['health'])
        self.image['health'] = pygame.transform.scale(self.image['health'], (400, 200))
        self.image['skill'] = pygame.image.load(images['skill'])
        self.image['skill'] = pygame.transform.scale(self.image['skill'], (60, 90))

        # Fetch the rectangle object
        # And update its position by setting x and y
        self.rect = self.image['walk'][0].get_rect()
        # Notice the two player's position cannot be the same
        self.rect.x = 75 + 600 * (index - 1)
        self.rect.y = 350
        # The size of the rect should be small
        self.rect.width = 60
        self.rect.height = 60

        # The amount of speed is by default
        self.vx = 9
        self.vy = 9
        # The player doesn't attack initially
        self.attack_flag = False
        self.skill_flag = False
        self.had_turn_back = True if index == 2 else False
        # Here I count the damage
        self.damage_counter = 0

    def walk(self, dire):
        # The dire stores the character's speed direction
        # It has 4 booleans. If its value is True, the it's supposed to move
        # Notice the player should not out of the range of the screen
        # And we are supposed not to use x, y
        # It seems the top, right, bottom and left don't work
        # And the amount of x,y is not exactly
        if dire[0] and self.rect.top >= 0:
            self.rect.y -= self.vy
        elif dire[1] and self.rect.x <= width - 50:
            self.rect.x += self.vx
        elif dire[2] and self.rect.y <= height - 100:
            self.rect.y += self.vy
        elif dire[3] and self.rect.x >= 0:
            self.rect.x -= self.vx

    def attack(self):
        # draw the picture when player is attacking
        screen.blit(self.image['attack'], self.rect)

    def injured(self):
        # draw the picture when player is injured
        screen.blit(self.image['injured'], self.rect)

    def release_skill(self):
        # draw the picture when player release the skill
        screen.blit(self.image['skill'], self.rect)

    def turn_back(self):
        # draw the picture when player turns back
        self.had_turn_back = not self.had_turn_back
        for key, value in self.image.items():
            if key != 'health':
                # If the type is  list
                if key == 'walk':
                    count = 0
                    for item in self.image['walk']:
                        # Resigning
                        self.image['walk'][count] = pygame.transform.flip(item, True, False)
                        count += 1
                else:
                    self.image[key] = pygame.transform.flip(value, True, False)


class Wave(pygame.sprite.Sprite):
    def __init__(self, player, img_surface):
        # Initialize Wave object
        pygame.sprite.Sprite.__init__(self)

        # Ensure which player the wave corresponds
        if player is player1:
            index = 1
        else:
            index = 2
        # Assign wave's image and rect
        self.image = pygame.transform.scale(img_surface, (80, 40))
        self.rect = self.image.get_rect()
        # Make the wave close to the player
        # Which reduces us a lot of trouble
        self.rect.x = player.rect.x
        self.rect.y = player.rect.y

        # Assign wave's properties, like speed
        # Notice the wave only move on x-axis
        self.v = 10
        # Check the existence of wave
        self.exist = False

    def move(self):
        self.rect.x += self.v * self.direction


# --------------------------FUNCTIONS-------------------------------
def set_font(txt, x, y, size=24):
    # Set font by giving its position and size
    # The default color is Black
    font = pygame.font.Font(None, size)
    text = font.render(txt, True, (0, 0, 0))
    text_rect = text.get_rect()
    text_rect.x = x
    text_rect.y = y
    screen.blit(text, text_rect)


def initialize_player():
    # initialize all properties
    player1.damage_counter = 0
    player2.damage_counter = 0
    player1.rect.x = 75
    player1.rect.y = 350
    player2.rect.x = 675
    player2.rect.y = 350


def game_over(winner):
    screen.fill((255, 255, 255))
    set_font(winner + " Wins!!", 170, 250, 100)
    set_font("(Enter 'R' to play again)", 180, 350, 50)
    pygame.display.flip()
    while True:
        for event in pygame.event.get():
            if event.type == QUIT:
                pygame.quit()
                exit()
            elif event.type == KEYDOWN:
                if event.key == K_r:
                    # Initialize all properties
                    initialize_player()
                    return
        # Notice there are two loop
        # each loop should be ended in time
        # The best way is to use return


def special_reaction(player):
    # Judge the player's condition
    # And blit the relevant image to rect
    global wave1_flag, wave2_flag

    # First assign the player
    if player is player2:
        attack_flag = player1.attack_flag
        direction = direction2
    else:
        attack_flag = player2.attack_flag
        direction = direction1

    # Check if the player is attacking
    # Use only one if, because we can only draw one picture at time
    if player.attack_flag:
        player.attack()

    # Check evey frame to see whether it
    # create a new wave
    elif player.skill_flag:
        skill.play()
        player.release_skill()
        if player == player1:
            wave1_flag = True
        else:
            wave2_flag = True

    # See whether the player's being attacked
    elif pygame.sprite.collide_rect(player1, player2) and attack_flag:
        player.injured()

    # Change the image when the player is moving
    # Use counter
    elif any(direction):
        global counter
        if counter < 2:
            screen.blit(player.image['walk'][counter], player.rect)
            counter += 1
        else:
            screen.blit(player.image['walk'][counter], player.rect)
            counter = 0
    else:
        screen.blit(player.image['walk'][0], player.rect)


def draw_health_value(index):
    # You must add the new rect rather than transform the current surface
    if index == 1:
        player = player1
    else:
        player = player2
    health_pos = 10 + 390 * (index - 1)
    screen.blit(player.image['health'], (health_pos, 10))
    for i in range(player.damage_counter):
        screen.blit(empty_health, (health_pos - 24 + 12 * i, 10))


# -------------------------INITIALIZE-------------------------------
# Load common images
empty_health = pygame.image.load(parent_directory + r'\V\empty_health.png')
empty_health = pygame.transform.scale(empty_health, (400, 200))
background_img = pygame.image.load(parent_directory + r'\V\background.png')
wave1_img = pygame.image.load(parent_directory + r'\V\wav1.png')
wave2_img = pygame.image.load(parent_directory + r'\V\wav2.png')

# The dictionary image1 stores the absolutely path of player1's images
images1, images2 = {}, {}
images1['walk0'] = parent_directory + r'\V\No1 player\No1walk0.png'
images1['walk1'] = parent_directory + r'\V\No1 player\No1walk1.png'
images1['walk2'] = parent_directory + r'\V\No1 player\No1walk2.png'
images1['attack'] = parent_directory + r'\V\No1 player\No1attack.png'
images1['injured'] = parent_directory + r'\V\No1 player\No1injured.png'
images1['health'] = parent_directory + r'\V\No1 player\No1health.png'
images1['skill'] = parent_directory + r'\V\No1 player\No1skill.png'
player1 = Player(images1, 1)
waves1 = pygame.sprite.Group()


images2['walk0'] = parent_directory + r'\V\No2 player\No2walk0.png'
images2['walk1'] = parent_directory + r'\V\No2 player\No2walk1.png'
images2['walk2'] = parent_directory + r'\V\No2 Player\No2walk2.png'
images2['attack'] = parent_directory + r'\V\No2 player\No2attack.png'
images2['injured'] = parent_directory + r'\V\No2 player\No2injured.png'
images2['health'] = parent_directory + r'\V\No2 player\No2health.png'
images2['skill'] = parent_directory + r'\V\No2 player\No2skill.png'
player2 = Player(images2, 2)
waves2 = pygame.sprite.Group()

# Load sounds
skill = pygame.mixer.Sound(r'D:\PycharmProjects\pygames\Fight\M\skill.wav')
skill.set_volume(0.25)
# Load background music and play it
music_address = parent_directory + r'\M\BGM.ogg'
pygame.mixer.music.load(music_address)
pygame.mixer.music.play(1, 0.0)
pygame.mixer.music.set_volume(0.2)

# Set Clock object
clock = pygame.time.Clock()

# Set direction with 4 booleans
# They are on behalf of TRBL
direction1, direction2 = [False, False, False, False], [False, False, False, False]

# Flags to see whether the user create new waves
wave1_flag = False
wave2_flag = False
# Record all waves's directions
wave1_dirs = []
wave2_dirs = []

# Some constant variables
# It seems the position of the rect is always integer
# That's because the size of your step is integer
epl = 4
# The counter is used to count player's step
counter = 0
# ----------------------------MAIN----------------------------------
while True:
    # Set condition to jump out of the infinity loop
    if player1.damage_counter == 17:
        game_over("Player2")
    elif player2.damage_counter == 17:
        game_over("Player1")

    # Don't forget to put this expression into the loop!
    # Otherwise the screen will change by the motion!
    screen.blit(background_img, (0, 0))
    # The font is necessary, too
    set_font("Player1", 110, 100)
    set_font("Player2", 630, 100)
    set_font("VS", 380, 10, 50)

    # Event loop begins...
    # Ps: the main role the event loop plays is to provide the conditions of the players
    for event in pygame.event.get():
        if event.type == QUIT:
            pygame.quit()
            exit()
        # PLAYER1
        elif event.type == KEYDOWN:
            # This block itself is ready to be put into a function
            # Store player's direction by check what the user has pressed
            # Set booleans to make the player to move constantly
            if event.key == K_UP:
                direction1[0] = True
            elif event.key == K_RIGHT:
                direction1[1] = True
            elif event.key == K_DOWN:
                direction1[2] = True
            elif event.key == K_LEFT:
                direction1[3] = True
            # Notice! It's time to attack the player's enemy
            # The user of player1 shall use 0 to attack
            elif event.key == K_KP0:
                player1.attack_flag = True
            elif event.key == K_KP_ENTER:
                player1.skill_flag = True

            # PLAYER2
            elif event.key == K_w:
                direction2[0] = True
            elif event.key == K_d:
                direction2[1] = True
            elif event.key == K_s:
                direction2[2] = True
            elif event.key == K_a:
                direction2[3] = True
            # Notice! It's time to attack the player's enemy
            # The user of player2 shall use SPACE to attack
            elif event.key == K_SPACE:
                player2.attack_flag = True
            elif event.key == K_x:
                player2.skill_flag = True

        elif event.type == KEYUP:
            # PLAYER1
            if event.key == K_UP:
                direction1[0] = False
            elif event.key == K_RIGHT:
                direction1[1] = False
            elif event.key == K_DOWN:
                direction1[2] = False
            elif event.key == K_LEFT:
                direction1[3] = False
            # Notice! It's time to give attack up!
            elif event.key == K_KP0:
                player1.attack_flag = False
                # If key_up and the 2 player have collide
                # Add the opposite's damage_counter
                if pygame.sprite.collide_rect(player1, player2):
                    player2.damage_counter += 1
            elif event.key == K_KP_ENTER:
                player1.skill_flag = False

            # PLAYER2
            elif event.key == K_w:
                direction2[0] = False
            elif event.key == K_d:
                direction2[1] = False
            elif event.key == K_s:
                direction2[2] = False
            elif event.key == K_a:
                direction2[3] = False
            # Notice! It's time to give attack up！
            elif event.key == K_SPACE:
                player2.attack_flag = False
                if pygame.sprite.collide_rect(player1, player2):
                    player1.damage_counter += 1
            elif event.key == K_x:
                player2.skill_flag = False
    # check moving ends
    # Event loop ends...

    # change their side by their position
    # I suppose it can't be precise
    if math.fabs(player1.rect.x - player2.rect.x) <= epl:
        player1.turn_back()
        player2.turn_back()

    # Now we can move the player according to the direction
    player1.walk(direction1)
    player2.walk(direction2)

    # Judge player's condition and react
    special_reaction(player1)
    special_reaction(player2)

    if wave1_flag:
        new_wave1 = Wave(player1, wave1_img)
        new_wave1.direction = -1 if player1.had_turn_back else 1
        waves1.add(new_wave1)
    if wave2_flag:
        new_wave2 = Wave(player2, wave2_img)
        new_wave2.direction = -1 if player2.had_turn_back else 1
        waves2.add(new_wave2)
    # Delete the wave which has moved out of range
    for wave in waves1:
        wave.move()
        if pygame.sprite.collide_rect(wave, player2):
            wave.kill()
            player2.damage_counter += 1
        if wave.rect.x <= 0 and wave.rect.x >= width:
            wave.kill()
    for wave in waves2:
        wave.move()
        if pygame.sprite.collide_rect(wave, player1):
            wave.kill()
            player1.damage_counter += 1
        if wave.rect.x <= 0 and wave.rect.x >= width:
            wave.kill()
    waves1.draw(screen)
    waves2.draw(screen)

    # Draw health value
    draw_health_value(1)
    draw_health_value(2)

    # Draw current time
    time = pygame.time.get_ticks()
    time_font = pygame.font.Font(None, 60)
    # This skill could calculate int time
    time_surface = time_font.render("Time:" + str(time // 1000), True, (0, 0, 0))
    screen.blit(time_surface, [330, 70])

    # Flush the screen
    pygame.display.flip()

    # Restore the wave's flag
    wave1_flag = False
    wave2_flag = False
# ------------------------------END------------------------------
