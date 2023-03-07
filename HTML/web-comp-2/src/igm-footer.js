// YOUR CODE GOES HERE
const template = document.createElement('template');
    template.innerHTML = `
    <style>
            :host{
                display: block;
                background-color: #ddd
            }

            span{
                color: #F76902;
                font-variant: small-caps;
                font-weight: bolder;
                font-family: sans-serif;
            }

            /* and here's the CSS to make the hr more "clickable"*/
            hr{
              border: 3px solid red;
            }
    </style>
    <span></span>
    <hr>
    `;

class IGMFooter extends HTMLElement{
    constructor()
    {
        super();

        this.attachShadow({mode: "open"});
        this.shadowRoot.appendChild(template.content.cloneNode(true));

        // put this at the end of the constructor
        if(!this.dataset.year) this.dataset.year = 1989;
        if(!this.dataset.text) this.dataset.text = "Bill & Ted";

        // This line of code will create an property named `span` for us, so that we don't have to keep calling this.shadowRoot.querySelector("span");
        this.span = this.shadowRoot.querySelector("span");
        
        this.count = 0;
    }

    static get observedAttributes()
    {
        return ["data-year", "data-text", "data-count"];
    }

    attributeChangedCallback(attributeName, oldVal, newVal)
    {
        console.log(attributeName, oldVal, newVal);
        this.render();
    }

    connectedCallback()
    {
        this.span.onclick = () => {
            let year = +this.dataset.year + 1;
            this.dataset.year = year;
            this.count += 1;
          };

          this.shadowRoot.querySelector("hr").onclick = () => {
            this.remove();
           }

        this.render();
    }

    disconnectedCallback()
    {
        this.span.onclick = null;
    }

    render()
    {
        const year = this.getAttribute('data-year') ? this.getAttribute('data-year') : "1995";

        const text = this.getAttribute('data-text') ? this.getAttribute('data-text') : "Nobody";

        const count = this.getAttribute('data-count') ? this.getAttribute('data-count') : this.count;

        this.shadowRoot.querySelector("span").innerHTML = `&copy; Copyright ${year}, ${text}, Count: ${this.count}`;
    }
} 
    
customElements.define('igm-footer', IGMFooter);