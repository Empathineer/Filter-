<h1 id="filter"><a data-id="" href="#filter">Filter</a></h1>
Implement a program that applies filters to BMPs, per the below.

<pre class="highlight"><code>$ ./filter -r image.bmp reflected.bmp
</code></pre>


<div class="highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./filter -r image.bmp reflected.bmp
</code></pre></div></div>

<h2 id="background"><a data-id="" href="#background">Background</a></h2>

<h3 id="bitmaps"><a data-id="" href="#bitmaps">Bitmaps</a></h3>

<p>Perhaps the simplest way to represent an image is with a grid of pixels (i.e., dots), each of which can be of a different color. For black-and-white images, we thus need 1 bit per pixel, as 0 could represent black and 1 could represent white, as in the below.</p>


<p>In this sense, then, is an image just a bitmap (i.e., a map of bits). For more colorful images, you simply need more bits per pixel. A file format (like <a href="https://en.wikipedia.org/wiki/BMP_file_format">BMP</a>, <a href="https://en.wikipedia.org/wiki/JPEG">JPEG</a>, or <a href="https://en.wikipedia.org/wiki/Portable_Network_Graphics">PNG</a>) that supports “24-bit color” uses 24 bits per pixel. (BMP actually supports 1-, 4-, 8-, 16-, 24-, and 32-bit color.)</p>

<p>A 24-bit BMP uses 8 bits to signify the amount of red in a pixel’s color, 8 bits to signify the amount of green in a pixel’s color, and 8 bits to signify the amount of blue in a pixel’s color. If you’ve ever heard of RGB color, well, there you have it: red, green, blue.</p>

<p>If the R, G, and B values of some pixel in a BMP are, say, <code class="highlighter-rouge">0xff</code>, <code class="highlighter-rouge">0x00</code>, and <code class="highlighter-rouge">0x00</code> in hexadecimal, that pixel is purely red, as <code class="highlighter-rouge">0xff</code> (otherwise known as <code class="highlighter-rouge">255</code> in decimal) implies “a lot of red,” while <code class="highlighter-rouge">0x00</code> and <code class="highlighter-rouge">0x00</code> imply “no green” and “no blue,” respectively.</p>

<h3 id="a-bitmap-more-technical"><a data-id="" href="#a-bitmap-more-technical">A Bit(map) More Technical</a></h3>

<p>Recall that a file is just a sequence of bits, arranged in some fashion. A 24-bit BMP file, then, is essentially just a sequence of bits, (almost) every 24 of which happen to represent some pixel’s color. But a BMP file also contains some “metadata,” information like an image’s height and width. That metadata is stored at the beginning of the file in the form of two data structures generally referred to as “headers,” not to be confused with C’s header files. (Incidentally, these headers have evolved over time. This problem uses the latest version of Microsoft’s BMP format, 4.0, which debuted with Windows 95.)</p>

<p>The first of these headers, called <code class="highlighter-rouge">BITMAPFILEHEADER</code>, is 14 bytes long. (Recall that 1 byte equals 8 bits.) The second of these headers, called <code class="highlighter-rouge">BITMAPINFOHEADER</code>, is 40 bytes long. Immediately following these headers is the actual bitmap: an array of bytes, triples of which represent a pixel’s color. However, BMP stores these triples backwards (i.e., as BGR), with 8 bits for blue, followed by 8 bits for green, followed by 8 bits for red. (Some BMPs also store the entire bitmap backwards, with an image’s top row at the end of the BMP file. But we’ve stored this problem set’s BMPs as described herein, with each bitmap’s top row first and bottom row last.) In other words, were we to convert the 1-bit smiley above to a 24-bit smiley, substituting red for black, a 24-bit BMP would store this bitmap as follows, where <code class="highlighter-rouge">0000ff</code> signifies red and <code class="highlighter-rouge">ffffff</code> signifies white; we’ve highlighted in red all instances of <code class="highlighter-rouge">0000ff</code>.</p>

<p>Because we’ve presented these bits from left to right, top to bottom, in 8 columns, you can actually see the red smiley if you take a step back.</p>

<p>To be clear, recall that a hexadecimal digit represents 4 bits. Accordingly, <code class="highlighter-rouge">ffffff</code> in hexadecimal actually signifies <code class="highlighter-rouge">111111111111111111111111</code> in binary.</p>

<p>Notice that you could represent a bitmap as a 2-dimensional array of pixels: where the image is an array of rows, each row is an array of pixels. Indeed, that’s how we’ve chosen to represent bitmap images in this problem.</p>

<h3 id="image-filtering"><a data-id="" href="#image-filtering">Image Filtering</a></h3>

<p>What does it even mean to filter an image? You can think of filtering an image as taking the pixels of some original image, and modifying each pixel in such a way that a particular effect is apparent in the resulting image.</p>

<h4 id="grayscale"><a data-id="" href="#grayscale">Grayscale</a></h4>

<p>One common filter is the “grayscale” filter, where we take an image and want to convert it to black-and-white. How does that work?</p>

<p>Recall that if the red, green, and blue values are all set to <code class="highlighter-rouge">0x00</code> (hexadecimal for <code class="highlighter-rouge">0</code>), then the pixel is black. And if all values are set to <code class="highlighter-rouge">0xff</code> (hexadecimal for <code class="highlighter-rouge">255</code>), then the pixel is white. So long as the red, green, and blue values are all equal, the result will be varying shades of gray along the black-white spectrum, with higher values meaning lighter shades (closer to white) and lower values meaning darker shades (closer to black).</p>

<p>So to convert a pixel to grayscale, we just need to make sure the red, green, and blue values are all the same value. But how do we know what value to make them? Well, it’s probably reasonable to expect that if the original red, green, and blue values were all pretty high, then the new value should also be pretty high. And if the original values were all low, then the new value should also be low.</p>

<p>In fact, to ensure each pixel of the new image still has the same general brightness or darkness as the old image, we can take the average of the red, green, and blue values to determine what shade of grey to make the new pixel.</p>

<p>If you apply that to each pixel in the image, the result will be an image converted to grayscale.</p>

<h4 id="sepia"><a data-id="" href="#sepia">Sepia</a></h4>

<p>Most image editing programs support a “sepia” filter, which gives images an old-timey feel by making the whole image look a bit reddish-brown.</p>

<p>An image can be converted to sepia by taking each pixel, and computing new red, green, and blue values based on the original values of the three.</p>

<p>There are a number of algorithms for converting an image to sepia, but for this problem, we’ll ask you to use the following algorithm. For each pixel, the sepia color values should be calculated based on the original color values per the below.</p>

<div class="highlighter-rouge"><div class="highlight"><pre class="highlight"><code>  sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
  sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
  sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
</code></pre></div></div>

<p>Of course, the result of each of these formulas may not be an integer, but each value could be rounded to the nearest integer. It’s also possible that the result of the formula is a number greater than 255, the maximum value for an 8-bit color value. In that case, the red, green, and blue values should be capped at 255. As a result, we can guarantee that the resulting red, green, and blue values will be whole numbers between 0 and 255, inclusive.</p>

<h4 id="reflection"><a data-id="" href="#reflection">Reflection</a></h4>

<p>Some filters might also move pixels around. Reflecting an image, for example, is a filter where the resulting image is what you would get by placing the original image in front of a mirror. So any pixels on the left side of the image should end up on the right, and vice versa.</p>

<p>Note that all of the original pixels of the original image will still be present in the reflected image, it’s just that those pixels may have rearranged to be in a different place in the image.</p>

<h4 id="blur"><a data-id="" href="#blur">Blur</a></h4>

<p>There are a number of ways to create the effect of blurring or softening an image. For this problem, we’ll use the “box blur,” which works by taking each pixel and, for each color value, giving it a new value by averaging the color values of neighboring pixels.</p>

<p>Consider the following grid of pixels, where we’ve numbered each pixel.</p>

<p>The new value of each pixel would be the average of the values of all of the pixels that are within 1 row and column of the original pixel (forming a 3x3 box). For example, each of the color values for pixel 6 would be obtained by averaging the original color values of pixels 1, 2, 3, 5, 6, 7, 9, 10, and 11 (note that pixel 6 itself is included in the average). Likewise, the color values for pixel 11 would be be obtained by averaging the color values of pixels 6, 7, 8, 10, 11, 12, 14, 15 and 16.</p>

<p>For a pixel along the edge or corner, like pixel 15, we would still look for all pixels within 1 row and column: in this case, pixels 10, 11, 12, 14, 15, and 16.</p>


<h2 id="understanding"><a data-id="" href="#understanding">Understanding</a></h2>

<p>Let’s now take a look at some of the files provided to you as distribution code to get an understanding for what’s inside of them.</p>

<h3 id="bmph"><a data-id="" href="#bmph"><code class="highlighter-rouge">bmp.h</code></a></h3>

<p>Open up <code class="highlighter-rouge">bmp.h</code> (as by double-clicking on it in the file browser) and have a look.</p>

<p>You’ll see definitions of the headers we’ve mentioned (<code class="highlighter-rouge">BITMAPINFOHEADER</code> and <code class="highlighter-rouge">BITMAPFILEHEADER</code>). In addition, that file defines <code class="highlighter-rouge">BYTE</code>, <code class="highlighter-rouge">DWORD</code>, <code class="highlighter-rouge">LONG</code>, and <code class="highlighter-rouge">WORD</code>, data types normally found in the world of Windows programming. Notice how they’re just aliases for primitives with which you are (hopefully) already familiar. It appears that <code class="highlighter-rouge">BITMAPFILEHEADER</code> and <code class="highlighter-rouge">BITMAPINFOHEADER</code> make use of these types.</p>

<p>Perhaps most importantly for you, this file also defines a <code class="highlighter-rouge">struct</code> called <code class="highlighter-rouge">RGBTRIPLE</code> that, quite simply, “encapsulates” three bytes: one blue, one green, and one red (the order, recall, in which we expect to find RGB triples actually on disk).</p>

<p>Why are these <code class="highlighter-rouge">struct</code>s useful? Well, recall that a file is just a sequence of bytes (or, ultimately, bits) on disk. But those bytes are generally ordered in such a way that the first few represent something, the next few represent something else, and so on. “File formats” exist because the world has standardized what bytes mean what. Now, we could just read a file from disk into RAM as one big array of bytes. And we could just remember that the byte at <code class="highlighter-rouge">array[i]</code> represents one thing, while the byte at <code class="highlighter-rouge">array[j]</code> represents another. But why not give some of those bytes names so that we can retrieve them from memory more easily? That’s precisely what the structs in <code class="highlighter-rouge">bmp.h</code> allow us to do. Rather than think of some file as one long sequence of bytes, we can instead think of it as a sequence of <code class="highlighter-rouge">struct</code>s.</p>

<h3 id="filterc"><a data-id="" href="#filterc"><code class="highlighter-rouge">filter.c</code></a></h3>

<p>Now, let’s open up <code class="highlighter-rouge">filter.c</code>. This file has been written already for you, but there are a couple important points worth noting here.</p>

<p>First, notice the definition of <code class="highlighter-rouge">filters</code> on line 11. That string tells the program what the allowable command-line arguments to the program are: <code class="highlighter-rouge">b</code>, <code class="highlighter-rouge">g</code>, <code class="highlighter-rouge">r</code>, and <code class="highlighter-rouge">s</code>. Each of them specifies a different filter that we might apply to our images: blur, grayscale, reflection, and sepia.</p>

<p>The next several lines open up an image file, make sure it’s indeed a BMP file, and read all of the pixel information into a 2D array called <code class="highlighter-rouge">image</code>.</p>

<p>Scroll down to the <code class="highlighter-rouge">switch</code> statement that begins on line 102. Notice that, depending on what <code class="highlighter-rouge">filter</code> we’ve chosen, a different function is called: if the user chooses filter <code class="highlighter-rouge">b</code>, the program calls the <code class="highlighter-rouge">blur</code> function; if <code class="highlighter-rouge">g</code>, then <code class="highlighter-rouge">grayscale</code> is called; if <code class="highlighter-rouge">r</code>, then <code class="highlighter-rouge">reflect</code> is called; and if <code class="highlighter-rouge">s</code>, then <code class="highlighter-rouge">sepia</code> is called. Notice, too, that each of these functions take as arguments the height of the image, the width of the image, and the 2D array of pixels.</p>

<p>These are the functions you’ll (soon!) implement. As you might imagine, the goal is for each of these functions to edit the 2D array of pixels in such a way that the desired filter is applied to the image.</p>

<p>The remaining lines of the program take the resulting <code class="highlighter-rouge">image</code> and write them out to a new image file.</p>

<h3 id="helpersh"><a data-id="" href="#helpersh"><code class="highlighter-rouge">helpers.h</code></a></h3>

<p>Next, take a look at <code class="highlighter-rouge">helpers.h</code>. This file is quite short, and just provides the function prototypes for the functions you saw earlier.</p>

<p>Here, take note of the fact that each function takes a 2D array called <code class="highlighter-rouge">image</code> as an argument, where <code class="highlighter-rouge">image</code> is an array of <code class="highlighter-rouge">height</code> many rows, and each row is itself another array of <code class="highlighter-rouge">width</code> many <code class="highlighter-rouge">RGBTRIPLE</code>s. So if <code class="highlighter-rouge">image</code> represents the whole picture, then <code class="highlighter-rouge">image[0]</code> represents the first row, and <code class="highlighter-rouge">image[0][0]</code> represents the pixel in the upper-left corner of the image.</p>

<h3 id="helpersc"><a data-id="" href="#helpersc"><code class="highlighter-rouge">helpers.c</code></a></h3>

<p>Now, open up <code class="highlighter-rouge">helpers.c</code>. Here’s where the implementation of the functions declared in <code class="highlighter-rouge">helpers.h</code> belong. But note that, right now, the implementations are missing! This part is up to you.</p>

<h3 id="makefile"><a data-id="" href="#makefile"><code class="highlighter-rouge">Makefile</code></a></h3>

<p>Finally, let’s look at <code class="highlighter-rouge">Makefile</code>. This file specifies what should happen when we run a terminal command like <code class="highlighter-rouge">make filter</code>. Whereas programs you may have written before were confined to just one file, <code class="highlighter-rouge">filter</code> seems to use multiple files: <code class="highlighter-rouge">filter.c</code>, <code class="highlighter-rouge">bmp.h</code>, <code class="highlighter-rouge">helpers.h</code>, and <code class="highlighter-rouge">helpers.c</code>. So we’ll need to tell <code class="highlighter-rouge">make</code> how to compile this file.</p>

<p>Try compiling <code class="highlighter-rouge">filter</code> for yourself by going to your terminal and running</p>

<div class="highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ make filter
</code></pre></div></div>

<p>Then, you can run the program by running:</p>

<div class="highlighter-rouge"><div class="highlight"><pre class="highlight"><code>$ ./filter -g images/yard.bmp out.bmp
</code></pre></div></div>

<p>which takes the image at <code class="highlighter-rouge">images/yard.bmp</code>, and generates a new image called <code class="highlighter-rouge">out.bmp</code> after running the pixels through the <code class="highlighter-rouge">grayscale</code> function. <code class="highlighter-rouge">grayscale</code> doesn’t do anything just yet, though, so the output image should look the same as the original yard.</p>

<h2 id="specification"><a data-id="" href="#specification">Specification</a></h2>

<p>Implement the functions in <code class="highlighter-rouge">helpers.c</code> such that a user can apply grayscale, sepia, reflection, or blur filters to their images.</p>

<ul class="fa-ul">
  <li data-marker="*"><span class="fa-li"><i class="fas fa-circle"></i></span>The function <code class="highlighter-rouge">grayscale</code> should take an image and turn it into a black-and-white version of the same image.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-circle"></i></span>The function <code class="highlighter-rouge">sepia</code> should take an image and turn it into a sepia version of the same image.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-circle"></i></span>The <code class="highlighter-rouge">reflect</code> function should take an image and reflect it horizontally.</li>
  <li data-marker="*"><span class="fa-li"><i class="fas fa-circle"></i></span>Finally, the <code class="highlighter-rouge">blur</code> function should take an image and turn it into a box-blurred version of the same image.</li>
</ul>

</ul>



