Explicación del bisect:
Hemos primero realizado 4 commits, y en el segundo hemos introducido un fallo, en este caso, hemos eliminado un ; de una línea de código.
Es un fallo tonto, y normalmente un programador promedio no continuaría haciendo commits después de esto ya que el código deja de funcionar y se encuentra fácil el error. De todas formas, no hace falta complicarlo mucho ya que el objetivo era mostrar cómo funciona el git bisect.

Los commits 1, 3 y 4 son cambios menores en el código.

Funcionamiento de git bisect:
- Primero se usa el comando: git bisect start
- Ahora tenemos que seleccionar el último commit para el bad bisect: git bisect bad
- Hacemos git log para ver los commits anteriores y copiar el hash del último commit en el que sabemos que no está el fallo.
- Con el hash copiado, hacemos: git bisect good <hash> , de esta forma marcamos el commit bueno.
- Ahora git irá alternando entre versiones entre el commit bad y el good e iremos verificando el código para ver si el fallo está o no. Conforme verifiquemos, escribiremos en el terminal: git bisect good / git bisect bad , en función de si esa rama temporal (la rama con el commit) tiene o no el fallo.
- En nuestro caso, primero ha elegido el commit 3, donde sí estaba el fallo. Hemos escrito git bisect bad, y nos ha mandado al commit 2, que es donde hemos introducido el fallo. Hemos vuelto a escribir git bisect bad y como no quedan mas commits entre este y el que hemos elegido como good bisect, ha determinado que el segundo commit es el que ha introducido el fallo. De esta forma hemos logrado identificar el commit que ha introducido el fallo usando git bisect.

hooks:
- Hemos activado el hook commit-msg quitando el .sample y hemos quitado los comentarios del signed off para que firme automáticamente si no hemos firmado nosotros.
- Primera prueba exitosa:
$ git last
commit 7b2a4c63b892fc2e5d75934f42f9d65804e2ae90 (HEAD -> rama-remota-1)
Author: plh5-ua <plh5@alu.ua.es>
Date:   Thu Dec 26 16:20:31 2024 +0100

    Prueba 2 del hook commit-msg, volvemos a intentar que añada la firma automáticamente
    Signed-off-by: plh5-ua <plh5@alu.ua.es>

Además hemos usado el alias local 'last' para sacar el último commit.
- Segunda prueba:
$ git commit -m "Prueba con la firma correcta.
>
> Signed-off-by: plh5-ua <plh5@alu.ua.es>"
[rama-remota-1 39a3fd5] Prueba con la firma correcta.
 1 file changed, 14 insertions(+), 1 deletion(-)

pablo@DePodador MINGW64 ~/Desktop/Universdidad/DCA/dca-ultima-practica (rama-remota-1)
$ git last
commit 39a3fd50f6ac6c1dd939685ae9b017bffd3e8240 (HEAD -> rama-remota-1)
Author: plh5-ua <plh5@alu.ua.es>
Date:   Thu Dec 26 16:24:46 2024 +0100

    Prueba con la firma correcta.

    Signed-off-by: plh5-ua <plh5@alu.ua.es>

- Tercera prueba:
$ git commit -m "Prueba firma duplicada:
>
> Signed-off-by: plh5-ua <plh5@alu.ua.es>
> Signed-off-by: plh5-ua <plh5@alu.ua.es>"
Duplicate Signed-off-by lines.

Confirmamos que el hook commit-msg funciona perfectamente.