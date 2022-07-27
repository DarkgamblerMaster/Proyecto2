// Se incluyen las bibliotecas a utilizar

#include <gtk/gtk.h>
#include <stdio.h>
#include <cairo.h>
#include <math.h>
#include <stdbool.h>

enum bloqueo_e{INACTIVO = 0, ACTIVO = 1};
enum letra_e{X = 0, O = 1, V = 2};

// Se declaran los elementos de la interfaz gráfica
GtkWidget *window;
GtkWidget *fixed1;
GtkWidget *button1;
GtkWidget *button2;
GtkWidget *button3;
GtkWidget *button4;
GtkWidget *button5;
GtkWidget *button6;
GtkWidget *button7;
GtkWidget *button8;
GtkWidget *button9;
GtkWidget *button_eleccion;
GtkWidget *label1;
GtkWidget *label2;
GtkWidget *label3;
GtkWidget *label4;
GtkWidget *label5;
GtkWidget *label6;
GtkWidget *label7;
GtkWidget *label8;
GtkWidget *label9;
GtkWidget *label_eleccion;
GtkWidget *label_resultado;
GtkWidget *draw;
GtkWidget *reset;
GtkBuilder *builder;

enum bloqueo_e bloqueo_elec = INACTIVO;
enum bloqueo_e bloqueo_buttons_click[] = {[0 ... 8] = INACTIVO};
enum letra_e letra = O;

// inicialmente el gato esta vacio, estos estados se
// iran actualizando a medida que se juega
enum letra_e estados[] = {[0 ... 8] = V};


int main(int argc, char *argv[]){
    // Se inicializa gtk
    gtk_init(&argc, &argv);
    
    // Se define la interfaz gráfica del archivo
    builder = gtk_builder_new_from_file("gato.glade");
    // Se define la ventana
    window = GTK_WIDGET(gtk_builder_get_object(builder, "window"));
    
    // Se conecta la señal de destrucción
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Se conectan las señales del builder
    gtk_builder_connect_signals(builder, NULL);

    // Se define la ventana fixed1
    fixed1 = GTK_WIDGET(gtk_builder_get_object(builder, "fixed1"));
    
    
    // BUTTONS
    // Se definen los botones con sus ID
    button1 = GTK_WIDGET(gtk_builder_get_object(builder, "button1"));
    button2 = GTK_WIDGET(gtk_builder_get_object(builder, "button2"));    
    button3 = GTK_WIDGET(gtk_builder_get_object(builder, "button3")); 
    button4 = GTK_WIDGET(gtk_builder_get_object(builder, "button4")); 
    button5 = GTK_WIDGET(gtk_builder_get_object(builder, "button5")); 
    button6 = GTK_WIDGET(gtk_builder_get_object(builder, "button6")); 
    button7 = GTK_WIDGET(gtk_builder_get_object(builder, "button7")); 
    button8 = GTK_WIDGET(gtk_builder_get_object(builder, "button8"));
    button9 = GTK_WIDGET(gtk_builder_get_object(builder, "button9"));
    button_eleccion = GTK_WIDGET(gtk_builder_get_object(builder, "button_eleccion"));

    // LABELS
    // Se definen las etiquetas con sus ID
    label1 = GTK_WIDGET(gtk_builder_get_object(builder, "label1"));
    label2 = GTK_WIDGET(gtk_builder_get_object(builder, "label2"));
    label3 = GTK_WIDGET(gtk_builder_get_object(builder, "label3"));
    label4 = GTK_WIDGET(gtk_builder_get_object(builder, "label4"));
    label5 = GTK_WIDGET(gtk_builder_get_object(builder, "label5"));
    label6 = GTK_WIDGET(gtk_builder_get_object(builder, "label6"));
    label7 = GTK_WIDGET(gtk_builder_get_object(builder, "label7"));
    label8 = GTK_WIDGET(gtk_builder_get_object(builder, "label8"));
    label9 = GTK_WIDGET(gtk_builder_get_object(builder, "label9"));
    label_eleccion = GTK_WIDGET(gtk_builder_get_object(builder, "label_eleccion"));
    label_resultado = GTK_WIDGET(gtk_builder_get_object(builder, "label_resultado"));

    // Se define el reset con su ID
    //draw = GTK_WIDGET(gtk_builder_get_object(builder, "draw"));
    reset = GTK_WIDGET(gtk_builder_get_object(builder, "reset"));
    
    // Se muestra la ventana 
    gtk_widget_show(window);
    gtk_main();

    
    return 0;
}

// Bloquea todas las entradas del gato
void bloquear_todo(){
    for(int k = 0; k < 9; k++){
        bloqueo_buttons_click[k] = ACTIVO;
    }
}

// Es el handler del boton reset
void on_reset_clicked(GtkButton *b){
    for(int k = 0; k < 9; k++){
        bloqueo_buttons_click[k] = INACTIVO;
        estados[k] = V;
    }
    gtk_label_set_text(GTK_LABEL(label1), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label2), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label3), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label4), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label5), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label6), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label7), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label8), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label9), (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "");
    gtk_label_set_text(GTK_LABEL(label_eleccion), (const gchar*) "inicia con: O");
    bloqueo_elec = INACTIVO;
    letra = O;
}

// Funcion para actualizar los estados del juego
void actualizar_estados(int index){
    if(letra == X){
        estados[index] = O;
    }
    else{
        estados[index] = X;
    }
}

// verifica si al presionar el boton 1 se consigue ganar
int verificar_ganador1(){
    bool estado01 = (estados[0] == estados[1]);
    bool estado02 = (estados[0] == estados[2]);
    bool hor_sup = (estado01 && estado02);
    bool estado03 = (estados[0] == estados[3]);
    bool estado06 = (estados[0] == estados[6]);
    bool ver_izq = (estado03 && estado06);
    bool estado04 = (estados[0] == estados[4]);
    bool estado08 = (estados[0] == estados[8]);
    bool diag1 = (estado04 && estado08);
    if(hor_sup || ver_izq || diag1 ){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 2 se consigue ganar
int verificar_ganador2(){
    bool estado01 = (estados[0] == estados[1]);
    bool estado02 = (estados[0] == estados[2]);
    bool hor_sup = (estado01 && estado02);
    bool estado14 = (estados[1] == estados[4]);
    bool estado17 = (estados[1] == estados[7]);
    bool ver_med = (estado14 && estado17);
    if(hor_sup || ver_med ){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 3 se consigue ganar
int verificar_ganador3(){
    bool estado01 = (estados[0] == estados[1]);
    bool estado02 = (estados[0] == estados[2]);
    bool hor_sup = (estado01 && estado02);
    bool estado25 = (estados[2] == estados[5]);
    bool estado28 = (estados[2] == estados[8]);
    bool ver_der = (estado25 && estado28);
    bool estado24 = (estados[2] == estados[4]);
    bool estado26 = (estados[2] == estados[6]);
    bool diag2 = (estado24 && estado26);
    if(hor_sup || ver_der || diag2 ){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 4 se consigue ganar
int verificar_ganador4(){
    bool estado03 = (estados[0] == estados[3]);
    bool estado36 = (estados[3] == estados[6]);
    bool ver_izq = (estado03 && estado36);
    bool estado34 = (estados[3] == estados[4]);
    bool estado35 = (estados[3] == estados[5]);
    bool hor_med = (estado34 && estado35);
    if(hor_med || ver_izq){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 5 se consigue ganar
int verificar_ganador5(){
    bool estado34 = (estados[3] == estados[4]);
    bool estado45 = (estados[4] == estados[5]);
    bool hor_med = (estado34 && estado45);
    bool estado14 = (estados[1] == estados[4]);
    bool estado74 = (estados[7] == estados[4]);
    bool ver_med = (estado14 && estado74);
    bool estado04 = (estados[0] == estados[4]);
    bool estado48 = (estados[4] == estados[8]);
    bool diag1 = (estado04 && estado48);
    bool estado24 = (estados[2] == estados[4]);
    bool estado46 = (estados[4] == estados[6]);
    bool diag2 = (estado24 && estado46);
    
    if(hor_med || ver_med || diag1 || diag2){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 6 se consigue ganar
int verificar_ganador6(){
    bool estado52 = (estados[5] == estados[2]);
    bool estado58 = (estados[5] == estados[8]);
    bool ver_der = (estado52 && estado58);
    bool estado54 = (estados[5] == estados[4]);
    bool estado53 = (estados[3] == estados[5]);
    bool hor_med = (estado54 && estado53);
    if(hor_med || ver_der){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 7 se consigue ganar
int verificar_ganador7(){
    bool estado60 = (estados[6] == estados[0]);
    bool estado63 = (estados[6] == estados[3]);
    bool ver_izq = (estado60 && estado63);
    bool estado67 = (estados[6] == estados[7]);
    bool estado68 = (estados[6] == estados[8]);
    bool hor_inf = (estado67 && estado68);
    bool estado64 = (estados[6] == estados[4]);
    bool estado62 = (estados[6] == estados[2]);
    bool diag2 = (estado64 && estado62);
    if(ver_izq || hor_inf || diag2){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 8 se consigue ganar
int verificar_ganador8(){
    bool estado71 = (estados[7] == estados[1]);
    bool estado74 = (estados[7] == estados[4]);
    bool ver_med = (estado71 && estado74);
    bool estado76 = (estados[7] == estados[6]);
    bool estado78 = (estados[7] == estados[8]);
    bool hor_inf = (estado76 && estado78);
    if(hor_inf || ver_med){
        return 1;
    }
    return 0;
}

// verifica si al presionar el boton 9 se consigue ganar
int verificar_ganador9(){
    bool estado82 = (estados[8] == estados[2]);
    bool estado85 = (estados[8] == estados[5]);
    bool ver_der = (estado82 && estado85);
    bool estado86 = (estados[8] == estados[6]);
    bool estado87 = (estados[8] == estados[7]);
    bool hor_inf = (estado86 && estado87);
    bool estado80 = (estados[8] == estados[0]);
    bool estado84 = (estados[8] == estados[4]);
    bool diag1 = (estado80 && estado84);
    if(ver_der || hor_inf || diag1){
        return 1;
    }
    return 0;
}

// handler del boton1, al presionarse realiza todas estas acciones
// los otros handlers similares hacen lo mismo para sus respectivos
// botones, por lo que este es el unico que ira comentado
void on_button1_clicked(GtkButton *b){
    // se ejecuta si el boton no esta bloqueado
    if(bloqueo_buttons_click[0] == INACTIVO){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        // esto pone la X o la O en el espacio segun sea el caso
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label1), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label1), (const gchar*) "X");
            letra = O;
        }
        // actualiza estados del juego
        actualizar_estados(0);
        // verifica si con apretar el boton 1 se consigue ganar
        if(verificar_ganador1()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }

        // bloquea el boton para que ya no haga nada aunque se presione
        bloqueo_buttons_click[0] = ACTIVO;
    }      
}

void on_button2_clicked(GtkButton *b){
    if(bloqueo_buttons_click[1] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label2), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label2), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(1);
        if(verificar_ganador2()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
        bloqueo_buttons_click[1] = ACTIVO;
    }      
}

void on_button3_clicked(GtkButton *b){
    if(bloqueo_buttons_click[2] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label3), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label3), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(2);
        if(verificar_ganador3()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
        bloqueo_buttons_click[2] = ACTIVO;
    }      
}


void on_button4_clicked(GtkButton *b){
    if(bloqueo_buttons_click[3] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label4), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label4), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(3);
        if(verificar_ganador4()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
        bloqueo_buttons_click[3] = ACTIVO;
    }      
}

void on_button5_clicked(GtkButton *b){
    if(bloqueo_buttons_click[4] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label5), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label5), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(4);
        if(verificar_ganador5()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
        bloqueo_buttons_click[4] = ACTIVO;
    }      
}


void on_button6_clicked(GtkButton *b){
    if(bloqueo_buttons_click[5] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label6), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label6), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(5);
        
        if(verificar_ganador6()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
       bloqueo_buttons_click[5] = ACTIVO;
    }      
}

void on_button7_clicked(GtkButton *b){
    if(bloqueo_buttons_click[6] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label7), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label7), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(6);
        if(verificar_ganador7()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
        bloqueo_buttons_click[6] = ACTIVO;
    }      
}

void on_button8_clicked(GtkButton *b){
    if(bloqueo_buttons_click[7] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label8), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label8), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(7);
        
        if(verificar_ganador8()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
        bloqueo_buttons_click[7] = ACTIVO;
    }      
}

void on_button9_clicked(GtkButton *b){
    if(bloqueo_buttons_click[8] == INACTIVO ){
        // bloquea el boton de eleccion inicial pues ya no es necesario
        if(bloqueo_elec == INACTIVO) bloqueo_elec = ACTIVO;
        if(letra == O){
            gtk_label_set_text(GTK_LABEL(label9), (const gchar*) "O");
            letra = X;
        }
        else{
            gtk_label_set_text(GTK_LABEL(label9), (const gchar*) "X");
            letra = O;
        }

        actualizar_estados(8);
        if(verificar_ganador9()){
            bloquear_todo();
            if(letra == O){
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: X");
            }
            else{
                gtk_label_set_text(GTK_LABEL(label_resultado)
                                   , (const gchar*) "GANADOR: O");
            }
        }
        bloqueo_buttons_click[8] = ACTIVO;
    }      
}


// este boton sirve para hacer la eleccion inicial, si presiona se empieza la
// partida con X, si no se presiona inicia con O, se ejecuta una sola vez
// y luego se bloquea, siempre y cuando no se presione uno de los botones 1-9
// en caso de que se presione uno de esos entonces este boton se bloquea.
void on_button_eleccion_clicked(GtkButton *b){
    if(bloqueo_elec == INACTIVO){
        // muestra en un label con que letra estamos iniciando el juego
        gtk_label_set_text(GTK_LABEL(label_eleccion), (const gchar*) "inicia con: X");
        // bloquea este boton
        bloqueo_elec = ACTIVO;
        // cambia la letra de O a X para iniciar el juego.
        letra = X;
    }
}
