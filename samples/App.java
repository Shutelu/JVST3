package samples;

/*
 * creation de la bibliotheque :  gcc -fPIC -I"$JAVA_HOME/include" -shared -o libmabibli.dylib PrintName.c   
 */

 /**
  * Class principal pour le lancement du programme de test
  * Dans cette exemple, on va charger une bibliotheque dynamique qui va afficher des informations qui existent dans un fichier C/C++
*/
public class App {
    
    //Chargement des bibliotheques, le nom de la bibliotheque est sans 'lib' devant
    static{
        System.loadLibrary("information");
    }

    /**
     * Le corps de la fonction est defini dans un fichier C/C++, 
     * le mot cle 'native' permet de dire que la methode est implementee dans un fichier C/C++
    */
    private static native int printCalcul(int a, int b);
    private static native String printName(String name);

    public static void main(String[] args) {
        int res_calcul = printCalcul(2,3);
        String res_name = printName("Simpson");

        System.out.println("Resultat du calcul : " + res_calcul);
        System.out.println("Nom : " + res_name);

    }
}
