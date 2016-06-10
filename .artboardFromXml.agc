{
  "resources" : {
    "href" : "resources\/graphics\/graphicContent.agc"
  },
  "artboards" : {
    "href" : "\/resources\/graphics\/graphicContent.agc"
  },
  "children" : {
    "text" : {
      "rules" : {
        "meta.ux.rangedStyles" : "$COPY rules.font subtags.meta.ux.rangedStyles",
        "text.paragraphs" : "$PARAGRAPH 1 text rules.style.font.size",
        "text.rawText" : "$text",
        "style.fill.color.value" : {
          "$color" : {
            "r" : "$red",
            "g" : "$green",
            "b" : "$blue"
          }
        },
        "text.frame" : {
          "$rect" : {
            "width" : "$width",
            "height" : "$height"
          }
        },
        "order" : [
          "transform",
          "name",
          "style.fill.color.value",
          "style.font",
          "text.frame",
          "text.rawText",
          "meta.ux.rangedStyles",
          "text.paragraphs"
        ],
        "type" : "text",
        "style.font" : {
          "$fontDescription" : {
            "size" : "$pointSize",
            "style" : "Regular",
            "postscriptName" : "$name",
            "family" : "$family"
          }
        },
        "name" : "$text",
        "transform" : {
          "$rect" : {
            "tx" : "$x",
            "ty" : "$y"
          }
        }
      }
    }
  },
  "version" : "1.5.0"
}