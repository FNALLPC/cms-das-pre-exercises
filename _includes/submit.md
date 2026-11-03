{% comment %}
  "Submit your answers" box for an episode. Usage: {% include submit.md episode=3 %}
  Links to the permanent answer form with the school year and episode pre-filled.
  Configure the form in _config.yml (`submission:`); see FORMS.md.
{% endcomment %}
{%- assign sub = site.submission -%}
{%- capture submit_url -%}
{{ sub.form_url }}?usp=pp_url&{{ sub.year_entry }}={{ site.year }}&{{ sub.episode_entry }}=Episode+{{ include.episode }}
{%- endcapture -%}

> ## Submit your answers
{%- if sub.form_url != "" %}
> Work through the **Question {{ include.episode }}.x** boxes on this page, then enter all your answers in the
> [CMSDAS@LPC{{ site.year }} answer form for Episode {{ include.episode }}]({{ submit_url }}).
> You can resubmit at any time; we keep your latest answers.
{%- else %}
> Work through the **Question {{ include.episode }}.x** boxes on this page.
> The CMSDAS@LPC{{ site.year }} answer form is not open yet; please check back soon.
{%- endif %}
> Stuck? Ask on [Mattermost]({{ site.mattermost_invitelink }}).
{: .challenge}
