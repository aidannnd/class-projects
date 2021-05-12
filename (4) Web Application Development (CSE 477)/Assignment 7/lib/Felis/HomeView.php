<?php


namespace Felis;


class HomeView extends View {
    /**
     * Constructor
     * Sets the page title and any other settings.
     */
    public function __construct() {
        $this->setTitle("Felis Investigations");
        $this->addLink("login.php", "Log in");
    }

    /**
     * Add content to the header
     * @return string Any additional comment to put in the header
     */
    protected function headerAdditional() {
        return <<<HTML
<p>Welcome to Felis Investigations!</p>
<p>Domestic, divorce, and carousing investigations conducted without publicity. People and cats shadowed
	and investigated by expert inspectors. Katnapped kittons located. Missing cats and witnesses located.
	Accidents, furniture damage, losses by theft, blackmail, and murder investigations.</p>
<p><a href="">Learn more</a></p>
HTML;
    }

    public function addTestimonial($quote, $cite) {
        $this->testimonials[$quote] = $cite;
    }

    public function testimonials() {
        $html = <<<HTML
<section class="testimonials">
    <h2>TESTIMONIALS</h2>
    <div class="left">
HTML;

        $count = 1;
        $start_right = true;
        foreach($this->testimonials as $quote => $cite) {
            if ($count <= count($this->testimonials) / 2) {

            $html .= <<<HTML
<blockquote>
    <p>$quote</p>
    <cite>$cite</cite>
</blockquote>
HTML;
            $count++;
            } else {
                if ($start_right) {
                    $html .= <<<HTML
</div>
    <div class="right">
    <blockquote>
        <p>$quote</p>
        <cite>$cite</cite>
    </blockquote>
HTML;
                    $start_right = false;
                } else {
                    $html .= <<<HTML
<blockquote>
    <p>$quote</p>
    <cite>$cite</cite>
</blockquote>
HTML;
                }
            }

        }

        $html .= <<<HTML
</div>
</section>
HTML;

        return $html;
    }

    private $testimonials = array();

}