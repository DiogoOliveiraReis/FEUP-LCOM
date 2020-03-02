#include <screens.h>

int score = 0;
extern unsigned day, month, year, hours, minutes, seconds;

int clearScreen()
{
    vg_draw_rectangle(0, 0, 1024, 768, 0);
    return 0;
}

int gameOverScreen()
{
    clearScreen();
    writeScore();
    writeHighscore();
    displayScores();

    xpm_map_t xpm_gameover = gameoverXPM;
    xpm_image_t img_gameover;
    uint8_t *sprite_gameover = vg_create_sprite(xpm_gameover, &img_gameover);
    vg_draw_sprite(sprite_gameover, img_gameover, 437, 50);

    xpm_map_t xpm_score = scorex;
    xpm_image_t img_score;
    uint8_t *sprite_score = vg_create_sprite(xpm_score, &img_score);
    vg_draw_sprite(sprite_score, img_score, 450, 150);

    drawInt(score, 530, 150);

    drawDate(day, month, year, hours, minutes, seconds, 437, 180);

    xpm_map_t xpm_highscore = highscore;
    xpm_image_t img_highscore;
    uint8_t *sprite_highscore = vg_create_sprite(xpm_highscore, &img_highscore);
    vg_draw_sprite(sprite_highscore, img_highscore, 5, 300);

    drawTopScores();

    xpm_map_t xpm_si2 = play;
    xpm_image_t img_si2;
    uint8_t *sprite_si2 = vg_create_sprite(xpm_si2, &img_si2);
    vg_draw_sprite(sprite_si2, img_si2, 392, 250);

    int ipc_status;
    message msg;
    uint32_t irq_set_timer = BIT(0);
    uint32_t irq_set_keyboard = BIT(1);
    uint32_t irq_set_mouse = BIT(12);
    uint32_t r;

    /* Timer Subscribe With Bit_No = 0 */
    uint8_t bit_no_timer = 0;
    if (timer_subscribe_int(&bit_no_timer) != 0)
        return 1;
    /* */

    /* Keyboard Subscribe With Bit_No = 1 */
    uint8_t bit_no = 1;
    if (keyboard_subscribe_int(&bit_no) != 0)
        return 1;
    /* */

    /* Mouse Subscribe With Bit_No = 12 */
    uint8_t bit_no_mouse = 12;
    if (mouse_subscribe_int(&bit_no_mouse) != 0)
        return 1;
    /* */

    mouse_enable_data_reporting();

    /* Device Driver Loop Start */
    while (scancode != ESC_KEY)
    { /* You may want to use a different condition */
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
        {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status))
        { /* received notification */
            switch (_ENDPOINT_P(msg.m_source))
            {
            case HARDWARE: /* hardware interrupt notification */
                if (msg.m_notify.interrupts & irq_set_timer)
                { /* subscribed interrupt */
                    /* process it */
                    memcpy(video_mem, double_buffer, 1024 * 768);
                }
                if (msg.m_notify.interrupts & irq_set_keyboard)
                { /* subscribed interrupt */
                    /* process it */
                    kbc_ih();
                    if (scancode == 0x19)
                    {
                        score = 0;
                        clearScreen();
                        proj_main_loop(0, 0);
                    }
                }
                if (msg.m_notify.interrupts & irq_set_mouse)
                { /* subscribed interrupt */
                    /* process it */
                    mouse_ih();
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */
            }
        }
        else
        { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }
    /* Device Driver Loop End */

    /* Timer Unsubscribe */
    if (timer_unsubscribe_int() == 1)
        return 1;
    /* */

    /* Keyboard Unsubscribe */
    if (keyboard_unsubscribe_int() == 1)
        return 1;
    /* */

    /* Mouse Unsubscribe */
    if (mouse_unsubscribe_int() == 1)
        return 1;
    /* */

    vg_exit();
    printf("Successfully Exited Space Invaders\n");

    return 0;
}

bool gameScreen(int level, int lives)
{
    xpm_map_t xpm_hp = livesXPM;
    xpm_image_t img_hp;
    uint8_t *sprite_hp = vg_create_sprite(xpm_hp, &img_hp);
    vg_draw_sprite(sprite_hp, img_hp, 5, 725);

    xpm_map_t xpm_score = scorex;
    xpm_image_t img_score;
    uint8_t *sprite_score = vg_create_sprite(xpm_score, &img_score);
    vg_draw_sprite(sprite_score, img_score, 5, 5);

    drawInt(score, 90, 5);

    Ship ship = createShip(486, 650);
    ship.hp = lives;
    drawInt(ship.hp, 85, 725);

    mouse_enable_data_reporting();

    int ipc_status;
    message msg;
    uint32_t irq_set_timer = BIT(0);
    uint32_t irq_set_keyboard = BIT(1);
    uint32_t irq_set_mouse = BIT(12);
    uint32_t r;

    int enemyRows = level % 6;
    int maxEnemyLasers = level;
    int enemySpeed = (int)level / 6 + 1;
    int totalEnemies = enemyRows * 10;
    int enemiesKilled = 0;
    Enemy *enemies = malloc(sizeof(Enemy) * 60);

    bool moveRight = false;
    bool moveLeft = false;
    bool shoot = false;
    bool enemiesMovingRight = true;

    Laser laser = createLaser(ship.x);

    Laser enemyLasers[maxEnemyLasers];

    int enemyIndex = 0;

    for (int i = 0; i < 10; i++)
    {
        for (int j = 0; j < enemyRows; j++)
        {
            enemies[enemyIndex] = createEnemy(10 + 75 * i, 50 + j * 70, 2 - (j % 3));
            enemyIndex++;
        }
    }

    xpm_map_t xpm_ship = shipXPM;
    xpm_image_t img_ship;
    uint8_t *sprite_ship = vg_create_sprite(xpm_ship, &img_ship);

    /* Timer Subscribe With Bit_No = 0 */
    uint8_t bit_no_timer = 0;
    if (timer_subscribe_int(&bit_no_timer) != 0)
        return 1;
    /* */

    /* Keyboard Subscribe With Bit_No = 1 */
    uint8_t bit_no = 1;
    if (keyboard_subscribe_int(&bit_no) != 0)
        return 1;
    /* */

    /* Mouse Subscribe With Bit_No = 12 */
    uint8_t bit_no_mouse = 12;
    if (mouse_subscribe_int(&bit_no_mouse) != 0)
        return 1;
    /* */

    /* Device Driver Loop Start */
    while (true)
    {
        /* Get a request message. */
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0)
        {
            printf("driver_receive failed with: %d", r);
            continue;
        }
        if (is_ipc_notify(ipc_status))
        { /* received notification */
            switch (_ENDPOINT_P(msg.m_source))
            {
            case HARDWARE: /* hardware interrupt notification */
                if (msg.m_notify.interrupts & irq_set_timer)
                { /* subscribed keyboard interrupt */
                    /* process it */

                    vg_draw_sprite(sprite_ship, img_ship, ship.x, ship.y);

                    //check if all enemies are dead, end game if so
                    if (enemiesKilled == totalEnemies)
                    {
                        clearScreen();
                        if (gameScreen(level + 1, lives + 1))
                            return true;
                    }

                    if (ship.hp <= 0)
                    {
                        return true;
                    }

                    //generate enemy shot
                    if (rand() % 100)
                    {
                        int enemyIndex = rand() % totalEnemies;
                        if (enemies[enemyIndex].alive)
                        {
                            for (int i = 0; i < maxEnemyLasers; i++)
                            {
                                if (!enemyLasers[i].active)
                                {
                                    enemyLasers[i].active = true;
                                    enemyLasers[i].x = enemies[enemyIndex].x;
                                    enemyLasers[i].y = enemies[enemyIndex].y;
                                    break;
                                }
                            }
                        }
                    }

                    //check collisions with all enemies
                    for (int i = 0; i < totalEnemies; i++)
                    {
                        if (enemies[i].alive) //only loop if enemy is alive
                        {
                            //if enemy is hit, erase and kill
                            if (laser.x >= (enemies[i].x) && laser.x <= (enemies[i].x + 30) && laser.y >= (enemies[i].y) && laser.y <= (enemies[i].y + 22))
                            {
                                eraseEnemy(enemies[i]);
                                enemies[i].alive = false;
                                enemiesKilled++;
                                score += enemies[i].score;
                                drawInt(score, 90, 5);
                                vg_erase_rectangle(laser.x, laser.y, 5, 15);
                                laser.y = 650;
                                shoot = false;
                            }

                            //if enemy wasnt hit update pos
                            if (enemies[i].alive)
                            {

                                if (enemiesMovingRight)
                                {
                                    enemies[i] = updateEnemy(enemies[i], enemySpeed, 0);
                                }

                                else
                                {
                                    enemies[i] = updateEnemy(enemies[i], -enemySpeed, 0);
                                }

                                //update movement direction
                                if (enemies[i].x >= 980)
                                {

                                    enemiesMovingRight = false;

                                    for (int j = 0; j < totalEnemies; j++)
                                    { //make all enemies go down
                                        if (enemies[j].alive)
                                        {
                                            enemies[j] = updateEnemy(enemies[j], -1, 20);
                                            if (enemies[j].y >= ship.y + 20)
                                                return true;
                                        }
                                    }
                                }

                                if (enemies[i].x <= 0)
                                {

                                    enemiesMovingRight = true;

                                    for (int j = 0; j < totalEnemies; j++)
                                    { //make all enemies go down
                                        if (enemies[j].alive)
                                        {
                                            enemies[j] = updateEnemy(enemies[j], 1, 20);
                                            if (enemies[j].y >= ship.y)
                                                return true;
                                        }
                                    }
                                }
                            }
                        }
                    }

                    //check enemyLaser collision with ship
                    for (int j = 0; j < maxEnemyLasers; j++)
                    {
                        if (enemyLasers[j].x > ship.x - 5 && enemyLasers[j].x < ship.x + 25 && enemyLasers[j].y > ship.y - 10 && enemyLasers[j].y < ship.y + 10)
                        {
                            enemyLasers[j].active = false;
                            ship.hp--;
                            drawInt(ship.hp, 85, 725);
                            vg_erase_rectangle(enemyLasers[j].x, enemyLasers[j].y, 5, 15);
                            break;
                        }
                    }

                    //update ship movement
                    if (moveRight)
                    {
                        vg_erase_sprite(sprite_ship, img_ship, ship.x, ship.y);
                        ship.x += 4;
                        vg_draw_sprite(sprite_ship, img_ship, ship.x, ship.y);
                    }

                    if (moveLeft)
                    {
                        vg_erase_sprite(sprite_ship, img_ship, ship.x, ship.y);
                        ship.x -= 4;
                        vg_draw_sprite(sprite_ship, img_ship, ship.x, ship.y);
                    }

                    //update ship shot
                    if (shoot)
                    {
                        vg_erase_rectangle(laser.x, laser.y, 5, 15);
                        laser.y -= 10;
                        vg_draw_rectangle(laser.x, laser.y, 5, 15, 10);
                        if (laser.y <= 25)
                        {
                            vg_erase_rectangle(laser.x, laser.y, 5, 15);
                            laser.y = ship.y;
                            shoot = false;
                        }
                    }

                    //update enemy lasers
                    for (int j = 0; j < maxEnemyLasers; j++)
                    {
                        if (enemyLasers[j].active)
                        {
                            vg_erase_rectangle(enemyLasers[j].x, enemyLasers[j].y, 5, 15);
                            enemyLasers[j].y += 3;
                            vg_draw_rectangle(enemyLasers[j].x, enemyLasers[j].y, 5, 15, 7);
                            if (enemyLasers[j].y >= ship.y)
                            {
                                vg_erase_rectangle(enemyLasers[j].x, enemyLasers[j].y, 5, 15);
                                enemyLasers[j].y = 0;
                                enemyLasers[j].active = false;
                            }
                        }
                    }
                    memcpy(video_mem, double_buffer, 1024 * 768);
                }
                /*INPUTS*/
                if (msg.m_notify.interrupts & irq_set_keyboard)
                { /* subscribed interrupt */
                    /* process it */
                    kbc_ih();
                    if (scancode == 0x32)
                        return true;

                    if (scancode == RIGHT_KEY)
                        moveRight = true;

                    if (scancode == RELEASE_RIGHT_KEY)
                        moveRight = false;

                    if (scancode == LEFT_KEY)
                        moveLeft = true;

                    if (scancode == RELEASE_LEFT_KEY)
                        moveLeft = false;

                    if (scancode == SPACEBAR_KEY && !shoot)
                    {
                        laser.x = ship.x;
                        shoot = true;
                    }
                    if (scancode == ESC_KEY)
                    {
                        return true;
                    }
                }
                if (msg.m_notify.interrupts & irq_set_mouse)
                { /* subscribed interrupt */
                    /* process it */
                    mouse_ih();
                    if (bytes_count == 3)
                    {
                        bytes_count = 0;
                    }
                    if (mouse_packet.bytes[0] == 0x09 && mouse_packet.bytes[1] == 0x00 && mouse_packet.bytes[2] == 0x00 &&
                        mouse_packet.lb)
                    {
                        vg_erase_sprite(sprite_ship, img_ship, ship.x, ship.y);
                        ship.x -= 4;
                        vg_draw_sprite(sprite_ship, img_ship, ship.x, ship.y);
                    }
                    if (mouse_packet.bytes[0] == 0x0a && mouse_packet.bytes[1] == 0x00 && mouse_packet.bytes[2] == 0x00 &&
                        mouse_packet.rb)
                    {
                        vg_erase_sprite(sprite_ship, img_ship, ship.x, ship.y);
                        ship.x += 4;
                        vg_draw_sprite(sprite_ship, img_ship, ship.x, ship.y);
                    }
                }
                break;
            default:
                break; /* no other notifications expected: do nothing */
            }
        }
        else
        { /* received a standard message, not a notification */
            /* no standard messages expected: do nothing */
        }
    }
    /* Device Driver Loop End */

    /* Timer Unsubscribe */
    if (timer_unsubscribe_int() == 1)
        return 1;
    /* */

    /* Keyboard Unsubscribe */
    if (keyboard_unsubscribe_int() == 1)
        return 1;
    /* */

    /* Mouse Unsubscribe */
    if (mouse_unsubscribe_int() == 1)
        return 1;
    /* */

    return false;
}
