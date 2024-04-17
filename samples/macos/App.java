package samples.macos;

/*
 * Commands
 * creation du fichier .h : javac -h . MaClass.java | -h=creation du header, .=emplacement courant pour generer le fichier .h, la class doit avoir une methode native
 * ca va genere un fichier .class et .h
 * 
 * ensuite on cree une implementation pour la methode
 * 
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
    private static native void printInformation();

    public static void main(String[] args) {
        printInformation();
    }
}
